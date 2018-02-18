#include <QFileDialog>
#include <QString>
#include <QtDebug>
#include <utility>

#include "engine.h"
#include "audioscript.h"
#include "plugin.h"

#include "audioscriptbuffer.h"

namespace {

int duplex(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data);

int input(void*, void *inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data);

int output(void* outputBuffer, void*, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data);

}

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
}

void Engine::findPlugins()
{
    QStringList libs =
            QFileDialog::getOpenFileNames(nullptr, tr("Select AudioScript Plugins"),
            ".", tr("Plugins (*.a, *.so, *.dll, *.dylib)"));
    for (QString libPath : libs) {
        Plugin plugin(libPath);
        if (plugin.spawnable()) {
            // Currently creating AudioScriptPlugin instance before inserting
            QString pluginName = plugin.name();
            auto retVal = m_plugins.emplace(std::make_pair(plugin.name(), std::move(plugin)));
            if (retVal.second) { // successful insertion
                emit pluginFound(retVal.first->second); // inserted AudioScriptPlugin
            }
        }
    }

}

void Engine::start()
{
    if (!m_rtAudio) {
        try {
            m_rtAudio = new RtAudio();
        } catch (const RtError& error) {
            qDebug() << error.getMessage();
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
    // TODO more code

    m_mode = mode;
    return true;
}

void Engine::stop()
{

}


int duplex(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data)
{

}

int input(void*, void* inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data)
{

}

int output(void* outputBuffer, void*, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void* data)
{

}
