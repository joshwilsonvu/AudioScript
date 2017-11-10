#ifndef AUDIOSCRIPTFACTORY_H
#define AUDIOSCRIPTFACTORY_H

#include "audioscript.h"

class AudioScriptFactory
{
public:
    virtual AudioScript* spawn();

    virtual std::string name();
};

#endif // AUDIOSCRIPTFACTORY_H
