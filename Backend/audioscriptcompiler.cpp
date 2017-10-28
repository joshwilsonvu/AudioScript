#include <QDir>
#include <QProcess>
#include <QtDebug>
#include <QString>

#include "audioscriptcompiler.h"

bool AudioScriptCompiler::build(QString className)
{
    return className.isEmpty();
}

bool AudioScriptCompiler::clean(QString className)
{
    return className.isEmpty();
}
