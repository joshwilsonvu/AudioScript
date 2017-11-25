#include <QFileDialog>
#include <QString>
#include <QtDebug>
#include <utility>

#include "audioscriptengine.h"
#include "audioscript.h"
#include "audioscriptplugin.h"

// class AudioScriptEngine
AudioScriptEngine::AudioScriptEngine(QObject *parent) : QObject(parent)
{
}

AudioScriptEngine::~AudioScriptEngine()
{

}

void AudioScriptEngine::findPlugins()
{
    QStringList libs =
            QFileDialog::getOpenFileNames(Q_NULLPTR, tr("Select AudioScript Plugins"),
            ".", tr("Plugins (*.a, *.so, *.dll, *.dylib)"));
    QStringList loaded;
    for (QString libPath : libs) {
        AudioScriptPlugin plugin(libPath);
        if (plugin.spawnable()) {
            // Currently creating AudioScriptPlugin instance before inserting
            QString pluginName = plugin.name();
            auto retVal = m_audioScriptPlugins.emplace(std::make_pair(plugin.name(), std::move(plugin)));
            if (retVal.second) {
                qDebug() << "Plugin found:" << libPath << "->" << pluginName;
                emit pluginFound((retVal.first->second));
            } else {
                qDebug() << "Plugin" << libPath << "->" << pluginName << "is duplicate.";
            }
        }
    }

}

