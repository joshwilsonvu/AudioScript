#include <QMessageBox>
#include <QMapIterator>

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


bool AudioScriptEngine::registerAudioScript(const QString& name)
{
    AudioScriptLibrary* lib = new AudioScriptLibrary(name);
    if (!lib->spawnable()) {
        m_audioScriptLibraries.insert(name, lib);
        return true;
    }
    return false;
}

