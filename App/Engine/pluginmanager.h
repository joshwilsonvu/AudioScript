#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>

#include "plugin.h"

class PluginManager : public QObject
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = nullptr);

signals:
    void pluginFound(Plugin&);

public slots:
    // make the engine aware of a new plugin
    // creates Plugin, adds to m_plugins, makes available
    void findPlugins();

private:
    std::map<QString, Plugin> m_plugins;

};

#endif // PLUGINMANAGER_H
