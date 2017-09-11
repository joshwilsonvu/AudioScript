#include "audioscript.h"
#include "audioscriptlibrary.h"

// class AudioScriptLibrary
AudioScriptLibrary::AudioScriptLibrary(const QString &name)
    : m_name(name),
      m_library(name),
      m_spawnFunction(nullptr)
{
    if (!m_library.isLoaded()) {
        return;
    }
    m_spawnFunction = reinterpret_cast<SpawnFunction>
            (m_library.resolve("spawn"));
    // m_spawnFunction only non-nullptr if everything has gone well
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
        return nullptr;
    }
    AudioScript* audioScript = m_spawnFunction();
    audioScript->setLibrary(this);
    return audioScript;
}

void AudioScriptLibrary::registerMember(MemberVariant&& member)
{
    m_members.push_back(std::move(member));
}
