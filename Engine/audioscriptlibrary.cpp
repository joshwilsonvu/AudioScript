#include <audioscript.h>
#include "audioscriptlibrary.h"

// class AudioScriptLibrary
AudioScriptLibrary::AudioScriptLibrary(QPluginLoader&& plugin)
    : m_plugin(plugin)
{
    m_factory = qobject_cast<AudioScriptFactory*>(m_plugin.instance());
    // m_factory only non-Q_NULLPTR if everything has gone well
}

AudioScriptLibrary::AudioScriptLibrary(QPluginLoader&& plugin)
    : m_plugin(plugin), m_spawnFunction(Q_NULLPTR)
{
    AudioScript* instance = qobject_cast<AudioScript*>(m_plugin.instance());

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

std::unique_ptr<AudioScript> AudioScriptLibrary::spawn()
{
    if (!spawnable()) {
        return Q_NULLPTR;
    }
    std::unique_ptr<AudioScript> audioScript(m_spawnFunction());
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
