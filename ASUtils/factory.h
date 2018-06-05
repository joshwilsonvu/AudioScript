#ifndef AS_FACTORY_H
#define AS_FACTORY_H

#include "script.h"
//#include "ui.h"
#include "globals.h"
#include <QtPlugin>

#define AS_FACTORY_IID "AudioScript.AS.Factory"

// macro to be included in private section of subclasses
#define AUDIOSCRIPTFACTORY Q_OBJECT \
    Q_PLUGIN_METADATA(IID AS_FACTORY_IID) \
    Q_INTERFACES(Factory)

namespace AS {

class ASUTILS_EXPORT Factory
{
public:
    virtual ~Factory();

    virtual Script* spawn() = 0;

    virtual const char* name() = 0;

    virtual const char* scriptInfo() = 0;

    //virtual void setupGUI(UI& gui) = 0;
};

} // AS

// tells meta-object system about interface
Q_DECLARE_INTERFACE(AS::Factory, AS_FACTORY_IID)

#endif // AUDIOSCRIPTFACTORY_H
