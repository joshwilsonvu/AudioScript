#include "pluginlibrary.h"


namespace AS {

PluginLibrary::PluginLibrary()
{

}

bool PluginLibrary::load(QString file) {
    auto plugin = Plugin(file);
    if (plugin.spawnable()) {
        m_plugins.emplace(std::make_pair(plugin.name(), std::move(plugin)));
        return true; // inserted or already existed
    }
    return false;
}

bool PluginLibrary::isLoaded(QString plugin)
{
    return m_plugins.count(plugin);
}

QString PluginLibrary::getInfo(QString plugin)
{
    auto iter = m_plugins.find(plugin);
    if (iter != m_plugins.end()) {
        return iter->second.info();
    } else {
        return "";
    }
}

} // AS
