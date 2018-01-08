#ifndef AUDIOSCRIPT_H
#define AUDIOSCRIPT_H

#include "globals.h"

//**********************
// AudioScript is the interface that effect classes will override and implement.
// It includes methods to return the effect's name, to process a sample, and
// optionally to show a custom dialog that allows the user to modify parameters.
// A default dialog is generated for the getter-setter pairs registered.
//**********************

class ASUTILS_EXPORT AudioScriptBuffer;

class ASUTILS_EXPORT AudioScript
{
public:
    virtual ~AudioScript();

    virtual AudioScriptBuffer process(AudioScriptBuffer input) = 0;

    virtual void reset() = 0;

};

#endif // AUDIOSCRIPT_H
