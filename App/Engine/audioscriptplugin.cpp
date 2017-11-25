#include <audioscript.h>
#include <QtDebug>
#include "audioscriptplugin.h"

// class AudioScriptLibrary
AudioScriptPlugin::AudioScriptPlugin(QString filename)
    : m_plugin(filename), m_factory(Q_NULLPTR)
{
    if (m_plugin.load()) {
        // only use const_cast in constructor
        // m_factory only non-null if everything has gone well
        m_factory = qobject_cast<AudioScriptFactory*>(m_plugin.instance());
        // initialize m_name
        const_cast<QString&>(m_name) = m_factory->name();
    } else {
        qDebug() << "Failed to load plugin: " << errorString();
    }
}

AudioScriptPlugin::AudioScriptPlugin(AudioScriptPlugin&& rhs)
    : m_plugin(rhs.m_plugin.fileName()), m_name(rhs.m_name), m_factory(rhs.m_factory)
{
    m_plugin.load();
    rhs.m_plugin.unload();
    rhs.m_factory = Q_NULLPTR;
}

AudioScriptPlugin::~AudioScriptPlugin()
{
    m_plugin.unload(); // release memory, deletes m_factory
}

QString AudioScriptPlugin::name() const
{
    return m_name;
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
        return Q_NULLPTR;
    }
    return m_factory->spawn();
}
