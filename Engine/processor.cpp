#include "processor.h"
#include "buffer.h"
#include "utils.h"
#include "exception.h"
#include "log.h"

#include <QtDebug>

namespace AS {

// C-style callback function
int Processor::duplex_callback(void* outputBuffer, void* inputBuffer,
                    unsigned int nBufferFrames, double streamTime,
                    unsigned int status, void* data)
{
    // forward to Processor instance for more OOP way of dealing with callback
    Processor* processor = (Processor*)data;
    return processor->duplex((sample_t*)outputBuffer, (sample_t*)inputBuffer,
                          nBufferFrames, streamTime, status);
}

Processor::Processor(ProcessGraph* processGraph)
    : m_processGraph(processGraph), m_numChannels(2)
{
    try {
        m_rtAudio = std::unique_ptr<RtAudio>(new RtAudio());
    } catch (const RtAudioError& error) {
        AS::log() << error.getMessage().c_str();
        return;
    }
    m_rtAudio->showWarnings(true);

    initializeAudio(); // opens stream but does not start
}

int Processor::numChannels() const
{
    return m_numChannels;
}

bool Processor::start()
{
    stop();

    if (!m_rtAudio) {
        // unsuccessful construction
        return false;
    }

    m_rtAudio->setStreamTime(0.0);
    try {
        m_rtAudio->startStream();
    } catch (const RtAudioError& e) {
        AS::log() << e.getMessage().c_str();
        stop();
        return false;
    }
    return true;
}

void Processor::stop()
{
    if (m_rtAudio && m_rtAudio->isStreamRunning()) {
        m_rtAudio->stopStream();
    }
}

Buffer Processor::process(Buffer buffer)
{
    // TODO
    return buffer;
}

int Processor::duplex(sample_t* outputBuffer, sample_t* inputBuffer,
                   unsigned int nBufferFrames, double streamTime,
                   unsigned int status)
{
    //AS::log() << "t =" << streamTime;
    if (status) {
        AS::log() << "Under/overflow detected.";
    }

    // read the input data
    unsigned int samples = nBufferFrames * this->numChannels();
    Buffer in(samples);
    std::copy(inputBuffer, inputBuffer + samples, in.begin());


    Buffer out;
    try {
        // process the data with the process() member function, which may throw
        out = this->process(std::move(in));
        AS::check(out.size() == samples,
                   "Output buffer length does not match input buffer length.");
    } catch (const AS::Exception& e) {
        AS::log() << e.what();
        return 2; // abort the stream immediately
    }

    // write the processed data
    std::copy(out.begin(), out.end(), (sample_t*)outputBuffer);

    AS::Log::instance().flush();

    return 0; // continue normally
}

void Processor::probeAudio()
{
    // Determine the number of devices available
    unsigned int devices = m_rtAudio->getDeviceCount();
    if (devices < 1) {
        AS::log() << "No audio devices found!";
        return;
    }

    // Scan through devices for various capabilities
    RtAudio::DeviceInfo info;
    for (unsigned int i=0; i<devices; i++)  {
        info = m_rtAudio->getDeviceInfo(i);
        if (info.probed) {
            AS::log() << "device =" << i << "name =" << info.name.c_str();
            AS::log() << "preferred sample rate =" << info.preferredSampleRate;
            AS::log() << "maximum output channels =" << info.outputChannels;
            AS::log() << "maximum input channels =" << info.inputChannels;
            AS::log() << "maximum duplex channels =" << info.duplexChannels;
            AS::log() << "default input device?" << info.isDefaultInput;
            AS::log() << "default output device?" << info.isDefaultOutput;
        } else {
            AS::log() << "device =" << i << "not probed";
        }
    }
}

void Processor::initializeAudio()
{
    // TODO let user view and select from available options
    unsigned int bufferSize = 1024;
    const int sampleRate = 44100;

    RtAudio::StreamParameters iParams, oParams;
    iParams.deviceId = m_rtAudio->getDefaultInputDevice();
    iParams.nChannels = m_numChannels;
    oParams.deviceId = m_rtAudio->getDefaultOutputDevice();
    oParams.nChannels = m_numChannels;

    RtAudio::StreamOptions options;
    options.flags = RTAUDIO_MINIMIZE_LATENCY;
    try {
        m_rtAudio->openStream(&oParams, &iParams, RTAUDIO_FLOAT32, sampleRate,
                              &bufferSize, &duplex_callback, (void*)this, &options);
        m_numChannels = std::min(iParams.nChannels, oParams.nChannels);
    } catch (const RtAudioError& error) {
        m_rtAudio.reset();
        AS::log() << error.getMessage().c_str();
    }
}

}
