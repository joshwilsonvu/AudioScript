#include "pluginmanager.h"

#include <QFileDialog>

PluginManager::PluginManager(QObject *parent)
    : QObject(parent)
{
}

PluginManager::~PluginManager()
{
    for (auto i = m_plugins.begin(); i != m_plugins.end(); ++i) {
        // make sure that all AudioScripts are deleted before unloading the code
        emit pluginRemoved(i->second);
    }
}

void PluginManager::findPlugins()
{
    QStringList libs =
            QFileDialog::getOpenFileNames(nullptr, tr("Select AudioScript Plugins"),
            ".", tr("Plugins (*.so, *.dll, *.dylib)"));
    for (QString libPath : libs) {
        Plugin plugin(libPath);
        if (plugin.spawnable()) {
            // Currently creating Plugin instance before inserting
            QString pluginName = plugin.name();
            auto retVal = m_plugins.emplace(std::make_pair(plugin.name(), std::move(plugin)));
            if (retVal.second) { // successful insertion
                emit pluginFound(retVal.first->second); // inserted Plugin
            }
        }
    }

}
