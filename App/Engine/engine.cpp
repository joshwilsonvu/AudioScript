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
      m_rtAudio(nullptr)
{
}

Engine::~Engine()
{
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
    const int numChannels = 1;
    unsigned int bufferSize = 512;
    const int sampleRate = 44100;

    if (!m_rtAudio) {
        try {
            m_rtAudio = new RtAudio();
        } catch (const RtAudioError& error) {
            qDebug() << error.getMessage().c_str();
            delete m_rtAudio;
            m_rtAudio = nullptr;
            return false;
        }
    } else if (m_rtAudio->isStreamOpen()) {
        if (m_rtAudio->isStreamRunning()) {
            m_rtAudio->stopStream();
        }
        m_rtAudio->closeStream();
    }

    m_rtAudio->showWarnings(true);
    if (m_rtAudio->getDeviceCount() < 1) {
        qDebug() << "No audio devices found!";
        return false;
    }
    RtAudio::StreamParameters iParams, oParams;
    iParams.deviceId = 0; // default device
    iParams.nChannels = 2;
    oParams.deviceId = 0; // default device
    oParams.nChannels = 2;

    try {
        m_rtAudio->openStream( &oParams, &iParams, RTAUDIO_FLOAT32, sampleRate,
                               &bufferSize, &duplex, (void*)this);
        m_rtAudio->startStream();
    } catch (const RtAudioError& e) {
        qDebug() << e.getMessage().c_str();
        if (m_rtAudio->isStreamOpen())
            m_rtAudio->closeStream();
        return false;
    }
    return true;
}

void Engine::stop()
{

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

}
