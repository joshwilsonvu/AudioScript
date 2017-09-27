#include <audioscript.h>
#include "audioscriptlibrary.h"

// class AudioScriptLibrary
AudioScriptLibrary::AudioScriptLibrary(QString name)
    : m_name(name),
      m_library(name),
      m_spawnFunction(Q_NULLPTR)
{
    if (!m_library.isLoaded()) {
        return;
    }
    m_spawnFunction = reinterpret_cast<SpawnFunction>
            (m_library.resolve("spawn"));
    // m_spawnFunction only non-Q_NULLPTR if everything has gone well
}

AudioScriptLibrary::~AudioScriptLibrary()
{
    m_library.unload(); // release memory
}

QString AudioScriptLibrary::name() const
{
    return m_name;
}

QString AudioScriptLibrary::errorString() const
{
    return m_library.errorString();
}

bool AudioScriptLibrary::spawnable() const
{
    return m_spawnFunction;
}

AudioScript* AudioScriptLibrary::spawn()
{
    if (!spawnable()) {
        return Q_NULLPTR;
    }
    AudioScript* audioScript = m_spawnFunction();
    audioScript->setLibrary(this);
    return audioScript;
}

void AudioScriptLibrary::registerMember(AudioScriptVariant&& variant, const std::string& name)
{
    QString qstring_name = QString::fromStdString(name);
    if (!m_members.contains(qstring_name)) {
        m_members.insert(qstring_name, variant);
    }
}
