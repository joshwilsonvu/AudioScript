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

    bool load(QString file);
    bool isLoaded(QString plugin);
    QString getInfo(QString plugin);
private:
    std::map<QString, Plugin> m_plugins;
};

} // AS

#endif // AS_PLUGINLIBRARY_H
