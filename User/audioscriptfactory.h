#ifndef AUDIOSCRIPTFACTORY_H
#define AUDIOSCRIPTFACTORY_H

#include "audioscript.h"

class AudioScriptFactory
{
public:
    virtual AudioScript* spawn();

    virtual std::string name();
};

// tells meta-object system about interface
Q_DECLARE_INTERFACE(AudioScriptFactory, "com.VUSESolutions.AudioScript.AudioScriptFactory/1.0")

#endif // AUDIOSCRIPTFACTORY_H
