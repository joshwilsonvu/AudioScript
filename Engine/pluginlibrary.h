#ifndef AS_PLUGINLIBRARY_H
#define AS_PLUGINLIBRARY_H

#include <map>

//#include <boost/multi_index_container.hpp>


class QString;

namespace AS {

class Plugin;

class PluginLibrary
{
public:
    PluginLibrary();

    // loads the plugin at the specified file and returns its package name, "" if failed
    QString load(QString file);

    Plugin* lookup(QString package);
private:
    std::map<QString, Plugin> m_plugins;
};

} // AS

#endif // AS_PLUGINLIBRARY_H
