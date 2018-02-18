#ifndef AUDIOSCRIPT_H
#define AUDIOSCRIPT_H

#include "globals.h"

class ASUTILS_EXPORT AudioScriptBuffer;

class ASUTILS_EXPORT AudioScript
{
public:
    virtual ~AudioScript();

    virtual AudioScriptBuffer process(AudioScriptBuffer input) = 0;

    virtual void reset() = 0;

};

#endif // AUDIOSCRIPT_H
