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
    Q_INTERFACES(AudioScriptFactory)

namespace AS {

class ASUTILS_EXPORT AudioScriptFactory
{
public:
    virtual ~AudioScriptFactory();

    virtual AudioScript* spawn() = 0;

    virtual const char* name() = 0;

    virtual const char* scriptInfo() = 0;

    virtual void setupGUI(AudioScriptUI& gui) = 0;

    /*
protected:
    template<class T>
    static AudioScriptVariant UI(const std::function<double(T*)>& getter);
    template<class T>
    static AudioScriptVariant UI(const std::function<float(T*)>& getter);
    template<class T>
    static AudioScriptVariant UI(const std::function<bool(T*)>& getter);
    template<class T>
    static AudioScriptVariant UI(const std::function<int(T*)>& getter);
    */
};

}

// tells meta-object system about interface
Q_DECLARE_INTERFACE(AS::AudioScriptFactory, AUDIOSCRIPTFACTORY_IID)

#endif // AUDIOSCRIPTFACTORY_H
