#include <QDir>
#include <QProcess>
#include <QtDebug>
#include <QString>

#include "audioscriptcompiler.h"

AudioScriptCompiler::AudioScriptCompiler(QObject* parent)
    : QObject(parent)
{
}

AudioScriptCompiler::~AudioScriptCompiler()
{
    qDebug() << "AudioScriptCompiler Destructor";
}


bool AudioScriptCompiler::build(QString className)
{
    return className.isEmpty();
}

bool AudioScriptCompiler::clean(QString className)
{
    return className.isEmpty();
}
