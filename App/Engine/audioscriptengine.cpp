#include <QFileDialog>
#include <QString>
#include <QtDebug>
#include <utility>

#include "audioscriptengine.h"
#include "audioscript.h"
#include "audioscriptplugin.h"

#include "audioscriptbuffer.h"

// class AudioScriptEngine
AudioScriptEngine::AudioScriptEngine(QObject *parent) : QObject(parent)
{
    AudioScriptBuffer::releaseMemory();
}

AudioScriptEngine::~AudioScriptEngine()
{

}

void AudioScriptEngine::findPlugins()
{
    QStringList libs =
            QFileDialog::getOpenFileNames(nullptr, tr("Select AudioScript Plugins"),
            ".", tr("Plugins (*.a, *.so, *.dll, *.dylib)"));
    for (QString libPath : libs) {
        AudioScriptPlugin plugin(libPath);
        if (plugin.spawnable()) {
            // Currently creating AudioScriptPlugin instance before inserting
            QString pluginName = plugin.name();
            auto retVal = m_audioScriptPlugins.emplace(std::make_pair(plugin.name(), std::move(plugin)));
            if (retVal.second) { // successful insertion
                emit pluginFound(retVal.first->second); // inserted AudioScriptPlugin
            }
        }
    }

}

