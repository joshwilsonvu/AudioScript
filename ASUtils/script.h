#ifndef AS_SCRIPT_H
#define AS_SCRIPT_H

#include "globals.h"

namespace AS {

class ASUTILS_EXPORT Buffer;

/// \brief The abstract base class of all audio scripts.
///
/// AudioScript Scripts are objects that can process floating point audio signals.
/// Every Script subclass must implement a process() method that accepts an
/// Buffer instance containing a buffer of data to be processed
/// and returns an appropriately processed buffer of the same size.
class ASUTILS_EXPORT Script
{
public:
    virtual ~Script();

    virtual Buffer process(Buffer input) = 0;

    virtual void init();

};

} // AS

#endif // AS_SCRIPT_H
