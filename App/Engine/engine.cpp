#include <QFileDialog>
#include <QString>
#include <QtDebug>
#include <utility>

#include "RtAudio.h"

#include "engine.h"
#include "audioscript.h"
#include "plugin.h"
#include "audioscriptbuffer.h"
#include "audioscriptutils.h"

int duplex(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data);

int input(void*, void *inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data);

int output(void* outputBuffer, void*, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data);

// class AudioScriptEngine
Engine::Engine(QObject *parent)
    : QObject(parent),
      m_rtAudio(nullptr),
      m_numChannels(2)
{
    start();
}

Engine::~Engine()
{
    stop();
    delete m_rtAudio;
    m_rtAudio = nullptr;
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

int Engine::channelCount() const
{
    return m_numChannels;
}

void Engine::findPlugins()
{
    QStringList libs =
            QFileDialog::getOpenFileNames(nullptr, tr("Select AudioScript Plugins"),
            ".", tr("Plugins (*.so, *.dll, *.dylib)"));
    for (QString libPath : libs) {
        Plugin plugin(libPath);
        if (plugin.spawnable()) {
            // TODO take out following debugging code
            m_scripts.push_back(plugin.spawn());
            start();

            // Currently creating Plugin instance before inserting
            QString pluginName = plugin.name();
            auto retVal = m_plugins.emplace(std::make_pair(plugin.name(), std::move(plugin)));
            if (retVal.second) { // successful insertion
                emit pluginFound(retVal.first->second); // inserted Plugin
            }
        }
    }

}

bool Engine::start()
{
    unsigned int bufferSize = 512;
    const int sampleRate = 44100;

    stop();

    if (!m_rtAudio) {
        try {
            m_rtAudio = new RtAudio();
            m_rtAudio->showWarnings(true);
        } catch (const RtAudioError& error) {
            qDebug() << error.getMessage().c_str();
            delete m_rtAudio;
            m_rtAudio = nullptr;
            return false;
        }
    }
    // Determine the number of devices available
    unsigned int devices = m_rtAudio->getDeviceCount();
    if (devices < 1) {
        qDebug() << "No audio devices found!";
        return false;
    }
    // Scan through devices for various capabilities
    RtAudio::DeviceInfo info;
    for ( unsigned int i=0; i<devices; i++ ) {
        info = m_rtAudio->getDeviceInfo( i );
        if (info.probed) {
            // Print, for example, the maximum number of output channels for each device
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

    RtAudio::StreamParameters iParams, oParams;
    iParams.deviceId = m_rtAudio->getDefaultInputDevice();
    iParams.nChannels = m_numChannels;
    oParams.deviceId = m_rtAudio->getDefaultOutputDevice();
    oParams.nChannels = m_numChannels;

    try {
        m_rtAudio->openStream( &oParams, &iParams, RTAUDIO_FLOAT32, sampleRate,
                               &bufferSize, &duplex, (void*)this);
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
    if (m_rtAudio && m_rtAudio->isStreamOpen()) {
        if (m_rtAudio->isStreamRunning()) {
            m_rtAudio->stopStream();
        }
        m_rtAudio->closeStream();
    }
}


int duplex(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data)
{
    // read the data
    sample_t* sInputBuffer = (sample_t*)inputBuffer;
    sample_t* sOutputBuffer = (sample_t*)outputBuffer;
    // TODO provide a way for the AudioScriptBuffer to take ownership of
    // sInputBuffer to avoid a copy
    AudioScriptBuffer in(nBufferFrames /* * numChannels */);
    std::copy(sInputBuffer, sInputBuffer + nBufferFrames /* * numChannels */,
              in.begin());

    // process the data
    Engine* engine = (Engine*)data;
    AudioScriptBuffer out = engine->process(std::move(in));

    // write the processed data
    AS::assert(out.size() == nBufferFrames /* * numChannels */);
    std::copy(out.begin(), out.end(), sOutputBuffer);
}

int input(void*, void* inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data)
{
    Q_UNUSED(inputBuffer);
    Q_UNUSED(nBufferFrames);
    Q_UNUSED(streamTime);
    if (status) {
        qDebug() << "Under/overflow detected.";
    }
}

int output(void* outputBuffer, void*, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data)
{
    Q_UNUSED(outputBuffer);
    Q_UNUSED(nBufferFrames);
    Q_UNUSED(streamTime);
    if (status) {
        qDebug() << "Under/overflow detected.";
    }
}
