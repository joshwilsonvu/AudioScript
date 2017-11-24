#ifndef AUDIOSCRIPTFACTORY_H
#define AUDIOSCRIPTFACTORY_H

#include "audioscript.h"
#include "audioscriptgui.h"
#include <QObject>
#include <QtPlugin>

#define AUDIOSCRIPTFACTORY_IID "com.VUSESolutions.AudioScript.AudioScriptFactory"

class AudioScriptFactory
{

public:
    virtual ~AudioScriptFactory() noexcept {}

    virtual AudioScript* spawn() = 0;

    virtual const char* name() = 0;

    virtual void setupGUI(AudioScriptGUI& gui) = 0;
};

// tells meta-object system about interface
Q_DECLARE_INTERFACE(AudioScriptFactory, AUDIOSCRIPTFACTORY_IID)

#endif // AUDIOSCRIPTFACTORY_H
