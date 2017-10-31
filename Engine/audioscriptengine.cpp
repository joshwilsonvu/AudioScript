#include <QMessageBox>
#include <QMapIterator>
#include <QString>

#include "audioscriptengine.h"
#include "audioscript.h"

// class AudioScriptEngine
AudioScriptEngine::AudioScriptEngine(QObject *parent) : QObject(parent)
{
}

AudioScriptEngine::~AudioScriptEngine()
{
    for (AudioScript* audioScript : m_activeAudioScripts) {
        delete audioScript;
    }
    for (auto iter = m_audioScriptLibraries.begin();
         iter != m_audioScriptLibraries.end(); ++iter) {
        delete iter.value();
    }
    m_activeAudioScripts.clear();
}

void AudioScriptEngine::clear()
{
    m_activeAudioScripts.clear();
}

void AudioScriptEngine::setAllEnabled(bool enabled)
{
    for (AudioScript* audioScript : m_activeAudioScripts) {
        audioScript->setEnabled(enabled);
    }
}

bool AudioScriptEngine::registerAudioScript(QString name)
{
    AudioScriptLibrary* lib = new AudioScriptLibrary(name);
    if (!lib->spawnable()) {
        m_audioScriptLibraries.insert(name, lib);
        return true;
    }
    return false;
}

