#include <QtDebug>
#include "audioscript.h"
#include "audioscriptfactory.h"
#include "audioscriptplugin.h"

// class AudioScriptLibrary
AudioScriptPlugin::AudioScriptPlugin(QString filename)
    : m_plugin(filename),
      m_factory(qobject_cast<AudioScriptFactory*>(m_plugin.instance())),
      m_name(m_factory ? m_factory->name() : "ERROR"),
      m_info(m_factory ? m_factory->scriptInfo() : "")
{
    // m_factory, m_name, and m_info are only set if everything has gone well
    if (!m_factory) {
        qDebug() << "Failed to load plugin: " << errorString();
    } else {
        qDebug() << "Plugin " << name() << " loaded.";
    }
}

AudioScriptPlugin::AudioScriptPlugin(AudioScriptPlugin&& rhs)
    : m_plugin(rhs.m_plugin.fileName()),
      m_factory(rhs.m_factory),
      m_name(rhs.m_name),
      m_info(rhs.m_info)
{
    m_plugin.load();
    rhs.m_plugin.unload();
    rhs.m_factory = nullptr;
}

AudioScriptPlugin::~AudioScriptPlugin()
{
    m_plugin.unload(); // release memory, deletes m_factory
    m_factory = nullptr;
}

QString AudioScriptPlugin::name() const
{
    return m_name;
}

QString AudioScriptPlugin::info() const
{
    return m_info;
}

QString AudioScriptPlugin::errorString() const
{
    return m_plugin.isLoaded() ? "" : m_plugin.errorString();
}

bool AudioScriptPlugin::spawnable() const
{
    return m_factory;
}

AudioScript* AudioScriptPlugin::spawn()
{
    if (!spawnable()) {
        return nullptr;
    }
    ++m_spawnedCount;
    return m_factory->spawn();
}

void AudioScriptPlugin::unspawn(AudioScript* spawned)
{
    if (spawned) {
        delete spawned;
        --m_spawnedCount;
    }
}
