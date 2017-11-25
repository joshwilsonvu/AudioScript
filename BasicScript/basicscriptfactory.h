#ifndef BASICSCRIPTFACTORY_H
#define BASICSCRIPTFACTORY_H

#include "audioscriptfactory.h"
#include "audioscriptgui.h"

class BasicScriptFactory : public QObject, public AudioScriptFactory
{
    AUDIOSCRIPTFACTORY

public:
    ~BasicScriptFactory() noexcept override;

    AudioScript* spawn() override;

    const char* name() override;

    void setupGUI(AudioScriptGUI& gui) override;
};

#endif // BASICSCRIPTFACTORY_H
