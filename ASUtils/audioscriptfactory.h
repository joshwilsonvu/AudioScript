#ifndef AUDIOSCRIPTFACTORY_H
#define AUDIOSCRIPTFACTORY_H

#include "audioscript.h"
#include "audioscriptui.h"
#include "globals.h"
#include <QtPlugin>

#define AUDIOSCRIPTFACTORY_IID "AudioScriptApp.AudioScriptFactory"

// macro to be included in private section of subclasses
#define AUDIOSCRIPTFACTORY Q_OBJECT \
    Q_PLUGIN_METADATA(IID AUDIOSCRIPTFACTORY_IID) \
    Q_INTERFACES(AS::AudioScriptFactory)

namespace AS {

class ASUTILS_EXPORT AudioScriptFactory
{
public:
    virtual ~AudioScriptFactory();

    virtual AudioScript* spawn() = 0;

    virtual const char* name() = 0;

    virtual const char* scriptInfo() = 0;

    virtual void setupGUI(AS::AudioScriptUI& gui) = 0;
};

}

// tells meta-object system about interface
Q_DECLARE_INTERFACE(AS::AudioScriptFactory, AUDIOSCRIPTFACTORY_IID)

#endif // AUDIOSCRIPTFACTORY_H
