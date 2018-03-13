#ifndef PLUGINLIBRARY_H
#define PLUGINLIBRARY_H

#include <QDockWidget>
#include <QListWidget>

#include "plugin.h"

class PluginLibrary : public QDockWidget
{
    Q_OBJECT
public:
    explicit PluginLibrary(QWidget *parent = nullptr);
    ~PluginLibrary();

    QSize sizeHint() const override;

    QString persistentDataDirectory() const;

signals:
    void pluginFound(Plugin&);
    void pluginRemoved(Plugin&);

public slots:
    // make the engine aware of a new plugin
    // creates Plugin, adds to m_plugins, makes available
    void findPlugins();

private:
    std::map<QString, Plugin> m_plugins;
    QListWidget m_list;
};

#endif // PLUGINLIBRARY_H
