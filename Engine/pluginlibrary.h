#ifndef AS_PLUGINLIBRARY_H
#define AS_PLUGINLIBRARY_H

#include "plugin.h"

#include <map>
#include <QObject>

//#include <boost/multi_index_container.hpp>

namespace AS {

class PluginLibrary : public QObject
{
    Q_OBJECT

public:
    PluginLibrary(QObject* parent = nullptr);

    Plugin* lookup(QString package);

public slots:
    // loads the plugin at the specified file and returns its package name, "" if failed
    QString load(QString file);

private:
    std::map<QString, Plugin> m_plugins;
};

} // AS

#endif // AS_PLUGINLIBRARY_H
