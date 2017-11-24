#include <audioscript.h>
#include <QtDebug>
#include "audioscriptlibrary.h"

// class AudioScriptLibrary
AudioScriptLibrary::AudioScriptLibrary(QString filename)
    : m_plugin(filename), m_factory(Q_NULLPTR)
{
    m_plugin.load();
    if (m_plugin.isLoaded()) {
        // m_factory only non-Q_NULLPTR if everything has gone well
        m_factory = qobject_cast<AudioScriptFactory*>(m_plugin.instance());
        // initialize m_name, only use const_cast in constructor
        const_cast<QString&>(m_name) = m_factory->name();
    } else {
        qDebug() << "Failed to load plugin: " << errorString();
    }
}

AudioScriptLibrary::~AudioScriptLibrary()
{
    //m_plugin.unload(); // release memory, deletes m_factory
}

QString AudioScriptLibrary::name() const
{
    return m_name;
}

QString AudioScriptLibrary::errorString() const
{
    return m_plugin.isLoaded() ? "" : m_plugin.errorString();
}

bool AudioScriptLibrary::spawnable() const
{
    return m_factory;
}

AudioScript* AudioScriptLibrary::spawn()
{
    if (!spawnable()) {
        return Q_NULLPTR;
    }
    return m_factory->spawn();
}
