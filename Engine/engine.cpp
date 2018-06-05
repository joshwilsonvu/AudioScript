
#include <QString>
#include <QtDebug>

#include "../engine.h"
#include "script.h"
#include "plugin.h"
#include "buffer.h"
#include "utils.h"

#include "pluginlibrary.h"
#include "processgraph.h"
#include "processor.h"

#include <QStandardPaths>

namespace AS {

QString persistentDataDirectory() {
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
}



// class Engine
Engine::Engine()
    : m_pluginLibrary(new PluginLibrary()),
      m_processGraph(new ProcessGraph()),
      m_processor(new Processor(m_processGraph))
{
}

Engine::~Engine()
{
    delete m_processor;
    delete m_processGraph;
    delete m_pluginLibrary;
}

bool Engine::load(QString file)
{
    return m_pluginLibrary->load(file);
}

bool Engine::isLoaded(QString plugin)
{
    return m_pluginLibrary->isLoaded(plugin);
}

} // AS


