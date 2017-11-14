#ifndef AUDIOSCRIPTFACTORY_H
#define AUDIOSCRIPTFACTORY_H

#include "audioscript.h"

class AudioScriptFactory
{
public:
    virtual ~AudioScriptFactory() = 0;

    virtual AudioScript* spawn() = 0;

    virtual std::string name() = 0;
};

// tells meta-object system about interface
Q_DECLARE_INTERFACE(AudioScriptFactory, "com.VUSESolutions.AudioScript.AudioScriptFactory/1.0")

#endif // AUDIOSCRIPTFACTORY_H
