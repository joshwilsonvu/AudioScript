#ifndef AUDIOSCRIPTCOMPILER_H
#define AUDIOSCRIPTCOMPILER_H

#include <QString>

class AudioScriptCompiler
{
public:

    static bool build(QString className);

    static bool clean(QString className);

private:
    AudioScriptCompiler() = delete;
    ~AudioScriptCompiler() = delete;

};

#endif // AUDIOSCRIPTCOMPILER_H
