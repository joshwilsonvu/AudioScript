
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



// class Engine
Engine::Engine()
    : m_pluginLibrary(new PluginLibrary()),
      m_processGraph(new ProcessGraph()),
      m_processor(new Processor(m_processGraph.get()))
{
}

Engine::~Engine()
{
}

bool Engine::start()
{
    return m_processor->start();
}

void Engine::stop()
{
    m_processor->stop();
}

QString Engine::load(QString file)
{
    QString package = m_pluginLibrary->load(file);
    return package;
}




} // AS


