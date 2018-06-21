#include <QtDebug>
#include "script.h"
#include "package.h"
#include "plugin.h"

namespace AS {

// class ScriptLibrary
Plugin::Plugin(QString filename)
    : m_plugin(filename),
      m_factory(qobject_cast<Package*>(m_plugin.instance()))
{
    // m_factory is only set if everything has gone well
    if (m_factory) {
        // null-terminated array of C-strings, for library compatibility
        for (auto names = m_factory->getNames(); *names; ++names) {
            m_names << QString(*names);
        }
    }
}

Plugin::Plugin(Plugin&& rhs)
    : m_plugin(rhs.m_plugin.fileName()),
      m_factory(rhs.m_factory)
{
    // reference counting lets plugin be transferred from rhs to this
    rhs.m_plugin.unload();
    rhs.m_factory = nullptr;
}

Plugin::~Plugin()
{
    m_factory = nullptr; // instance still accessible by recreating the same Plugin
}

bool Plugin::unload()
{
    if (m_plugin.unload()) { // release memory, deletes m_factory
        m_factory = nullptr;
        return true;
    }
    return false;
}

QString Plugin::errorString() const
{
    return m_plugin.isLoaded() ? "" : m_plugin.errorString();
}

QStringList Plugin::getNames() const
{
    return m_names;
}

QString Plugin::getPackage() const
{
    return m_factory ? m_factory->getPackage() : "";
}

bool Plugin::canGet(QString scriptName) const
{
    if (scriptName.isEmpty()) {
        return m_factory;
    }
    return m_factory && m_factory->canGet(scriptName.toLocal8Bit().constData());
}

Script* Plugin::get(QString scriptName) const
{
    auto scriptNameStr = scriptName.toLocal8Bit();
    if (!canGet(scriptNameStr.constData())) {
        return nullptr;
    }
    return m_factory->get(scriptNameStr.constData());
}

QString Plugin::getDescription(QString scriptName) const
{
    return m_factory->getDescription(scriptName.toLocal8Bit().constData());
}

} // AS
