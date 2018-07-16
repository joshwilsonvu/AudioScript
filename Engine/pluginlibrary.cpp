#include "pluginlibrary.h"

#include <QString>

namespace AS {

PluginLibrary::PluginLibrary(QObject* parent)
    : QObject(parent)
{

}

QString PluginLibrary::load(QString file) {
    auto plugin = Plugin(file);
    if (plugin.canGet()) {
        auto package = plugin.getPackage();
        m_plugins.emplace(std::make_pair(package, std::move(plugin)));
        return package; // inserted or already existed
    }
    return "";
}

Plugin* PluginLibrary::lookup(QString package)
{
    auto iter = m_plugins.find(package);
    if (iter == m_plugins.end()) {
        return nullptr;
    }
    return &iter->second;
}

} // AS
