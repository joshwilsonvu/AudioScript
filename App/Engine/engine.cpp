
#include <QString>
#include <QtDebug>

#include "RtAudio.h"

#include "engine.h"
#include "audioscript.h"
#include "plugin.h"
#include "audioscriptbuffer.h"
#include "audioscriptutils.h"

// C-style callback function
int duplex_callback(void* outputBuffer, void* inputBuffer,
                    unsigned int nBufferFrames, double streamTime,
                    RtAudioStreamStatus status, void* data)
{
    // forward to engine for more OOP way of dealing with callback
    Engine* engine = (Engine*)data;
    return engine->duplex((sample_t*)outputBuffer, (sample_t*)inputBuffer,
                          nBufferFrames, streamTime, status);
}

// class AudioScriptEngine
Engine::Engine()
    : m_rtAudio(nullptr),
      m_numChannels(2)
{
    try {
        m_rtAudio = std::unique_ptr<RtAudio>(new RtAudio());
    } catch (const RtAudioError& error) {
        qDebug() << error.getMessage().c_str();
    }
    m_rtAudio->showWarnings(true);

    probeAudio();
    initializeAudio(); // opens stream but does not start
}

Engine::~Engine()
{
    stop();
    for (AudioScript* i : m_scripts) {
        delete i;
    }
}

AudioScriptBuffer Engine::process(AudioScriptBuffer input)
{
    for (AudioScript* i : m_scripts) {
        input = i->process(std::move(input));
    }
    return input;
}

int Engine::numChannels() const
{
    return m_numChannels;
}

bool Engine::start()
{
    stop();

    if (!m_rtAudio) {
        // unsuccessful construction
        return false;
    }

    try {
        m_rtAudio->startStream();
    } catch (const RtAudioError& e) {
        qDebug() << e.getMessage().c_str();
        stop();
        return false;
    }
    return true;
}

void Engine::stop()
{
    if (m_rtAudio && m_rtAudio->isStreamRunning()) {
        m_rtAudio->stopStream();
    }
}

int Engine::duplex(sample_t* outputBuffer, sample_t* inputBuffer,
                   unsigned int nBufferFrames, double streamTime,
                   unsigned long status)
{
    qDebug() << "t =" << streamTime;
    if (status) {
        qDebug() << "Under/overflow detected.";
    }

    // read the data
    unsigned int samples = nBufferFrames * this->numChannels();
    AudioScriptBuffer in(samples);
    std::copy(inputBuffer, inputBuffer + samples, in.begin());

    // process the data with the process() member function
    AudioScriptBuffer out = this->process(std::move(in));

    // write the processed data
    AS::assert(out.size() == samples);
    std::copy(out.begin(), out.end(), (sample_t*)outputBuffer);

    return 0;
}

void Engine::probeAudio()
{
    // Determine the number of devices available
    unsigned int devices = m_rtAudio->getDeviceCount();
    if (devices < 1) {
        qDebug() << "No audio devices found!";
        return;
    }

    // Scan through devices for various capabilities
    RtAudio::DeviceInfo info;
    for (unsigned int i=0; i<devices; i++)  {
        info = m_rtAudio->getDeviceInfo(i);
        if (info.probed) {
            qDebug() << "device =" << i << "name =" << info.name.c_str();
            qDebug() << "preferred sample rate =" << info.preferredSampleRate;
            qDebug() << "maximum output channels =" << info.outputChannels;
            qDebug() << "maximum input channels =" << info.inputChannels;
            qDebug() << "maximum duplex channels =" << info.duplexChannels;
            qDebug() << "default input device?" << info.isDefaultInput;
            qDebug() << "default output device?" << info.isDefaultOutput;
        } else {
            qDebug() << "device =" << i << "not probed";
        }
    }
}

void Engine::initializeAudio()
{
    // TODO let user view and select from available options
    unsigned int bufferSize = 1024;
    const int sampleRate = 44100;

    RtAudio::StreamParameters iParams, oParams;
    iParams.deviceId = m_rtAudio->getDefaultInputDevice();
    iParams.nChannels = m_numChannels;
    oParams.deviceId = m_rtAudio->getDefaultOutputDevice();
    oParams.nChannels = m_numChannels;
    try {
        m_rtAudio->openStream(&oParams, &iParams, RTAUDIO_FLOAT32, sampleRate,
                              &bufferSize, &duplex_callback, (void*)this);
        m_numChannels = std::min(iParams.nChannels, oParams.nChannels);
    } catch (const RtAudioError& error) {
        m_rtAudio.reset();
        qDebug() << error.getMessage().c_str();
    }
}


