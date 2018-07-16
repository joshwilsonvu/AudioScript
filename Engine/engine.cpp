
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
Engine::Engine(QObject* parent)
    : QObject(parent),
      m_pluginLibrary(new PluginLibrary()),
      m_processGraph(new ProcessGraph()),
      m_processor(new Processor(m_processGraph.get()))
{
}

Engine::~Engine()
{
}

void Engine::start()
{
    if (m_processor->start()) {
        emit started();
    }
}

void Engine::stop()
{
    m_processor->stop();
    emit stopped();
}

QString Engine::load(QString file)
{
    QString package = m_pluginLibrary->load(file);
    emit pluginLoaded(package);
    return package;
}




} // AS


