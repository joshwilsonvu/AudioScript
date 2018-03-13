#include <QtDebug>
#include "audioscript.h"
#include "audioscriptfactory.h"
#include "plugin.h"

// class AudioScriptLibrary
Plugin::Plugin(QString filename)
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

Plugin::Plugin(Plugin&& rhs)
    : m_plugin(rhs.m_plugin.fileName()),
      m_factory(rhs.m_factory),
      m_name(rhs.m_name),
      m_info(rhs.m_info)
{
    // reference counting lets pluging be transferred from rhs to this
    m_plugin.load();
    rhs.m_plugin.unload();
    rhs.m_factory = nullptr;
}

Plugin::~Plugin()
{
    m_plugin.unload(); // release memory, deletes m_factory
    m_factory = nullptr;
}

QString Plugin::name() const
{
    return m_name;
}

QString Plugin::info() const
{
    return m_info;
}

QString Plugin::errorString() const
{
    return m_plugin.isLoaded() ? "" : m_plugin.errorString();
}

bool Plugin::spawnable() const
{
    return m_factory;
}

AudioScript* Plugin::spawn()
{
    if (!spawnable()) {
        return nullptr;
    }
    return m_factory->spawn();
}
