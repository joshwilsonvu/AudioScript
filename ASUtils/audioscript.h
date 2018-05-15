#ifndef AUDIOSCRIPT_H
#define AUDIOSCRIPT_H

#include "globals.h"

class ASUTILS_EXPORT AudioScriptBuffer;

/// \brief The abstract base class of all audio scripts.
///
/// Audio scripts are objects that can process floating point audio signals.
/// Every AudioScript must implement a process() method that accepts an
/// AudioScriptBuffer instance containing a buffer of data to be processed
/// and returns an appropriately processed buffer of the same size.
class ASUTILS_EXPORT AudioScript
{
public:
    virtual ~AudioScript();

    virtual AudioScriptBuffer process(AudioScriptBuffer input) = 0;

    virtual void reset();

};

#endif // AUDIOSCRIPT_H
