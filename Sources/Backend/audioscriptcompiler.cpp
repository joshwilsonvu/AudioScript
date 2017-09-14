#include <QDir>
#include <QProcess>
#include <QtDebug>

#include "audioscriptcompiler.h"

AudioScriptCompiler::AudioScriptCompiler(QObject* parent)
    : QObject(parent)
{
}

AudioScriptCompiler::~AudioScriptCompiler()
{
    qDebug() << "AudioScriptCompiler Destructor";
}

/*
bool AudioScriptCompiler::build(const QString& className)
{
    return className.isEmpty();
}

bool AudioScriptCompiler::buildAll(const QStringList& classes)
{
    return classes.isEmpty();
}

bool AudioScriptCompiler::clean(const QString& className)
{
    return className.isEmpty();
}

bool AudioScriptCompiler::cleanAll(const QStringList& classes)
{
    return classes.isEmpty();
}

bool AudioScriptCompiler::rebuild(const QString& className)
{
    return clean(className) && build(className);
}

bool AudioScriptCompiler::rebuildAll(const QStringList& classes)
{
    return cleanAll(classes) && buildAll(classes);
}
*/
