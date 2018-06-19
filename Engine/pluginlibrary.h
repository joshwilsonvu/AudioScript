#ifndef AS_PLUGINLIBRARY_H
#define AS_PLUGINLIBRARY_H

#include <map>

class QString;

namespace AS {

class Plugin;

class PluginLibrary
{
public:
    PluginLibrary();

    // loads the plugin at the specified file and returns its name, "" if failed
    QString load(QString file);
    bool isLoaded(QString plugin);
    QString getInfo(QString plugin);
private:
    std::map<QString, Plugin> m_plugins;
};

} // AS

#endif // AS_PLUGINLIBRARY_H
