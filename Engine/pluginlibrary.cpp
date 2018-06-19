#include "pluginlibrary.h"
#include "plugin.h"

#include <QString>

namespace AS {

PluginLibrary::PluginLibrary()
{

}

QString PluginLibrary::load(QString file) {
    auto plugin = Plugin(file);
    if (plugin.spawnable()) {
        auto name = plugin.name();
        m_plugins.emplace(std::make_pair(name, std::move(plugin)));
        return name; // inserted or already existed
    }
    return "";
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
