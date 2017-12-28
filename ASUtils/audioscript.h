#ifndef AS_AUDIOSCRIPT_H
#define AS_AUDIOSCRIPT_H

#include "globals.h"

//**********************
// AudioScript is the interface that effect classes will override and implement.
// It includes methods to return the effect's name, to process a sample, and
// optionally to show a custom dialog that allows the user to modify parameters.
// A default dialog is generated for the getter-setter pairs registered.
//**********************

namespace AS {

class ASUTILS_EXPORT AudioScript
{
public:
    virtual ~AudioScript();

    virtual sample_t process(sample_t sample) = 0;

    virtual void reset() = 0;

};

}

#endif // AUDIOSCRIPT_H
