#ifndef ENGINE_H
#define ENGINE_H

#include "plugin.h"

#include <QObject>
#include <map>

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);
    ~Engine();


signals:
    void pluginFound(Plugin&);

public slots:
    // make the engine aware of a new plugin
    // creates Plugin, adds to m_plugins, makes available
    void findPlugins();

    // TODO for starting out, I am going to make this start in duplex
    // mode, without any other options. Once the minimum viable product
    // is working, more options can be added and the interface can be smoothed.
    void start();

    void stop();

private:




    std::map<QString, Plugin> m_plugins;
};

#endif // ENGINE_H
