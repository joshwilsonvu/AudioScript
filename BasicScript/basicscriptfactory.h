#ifndef BASICSCRIPTFACTORY_H
#define BASICSCRIPTFACTORY_H

#include "audioscriptfactory.h"
#include "audioscriptgui.h"

class BasicScriptFactory : public QObject, public AudioScriptFactory
{
    AUDIOSCRIPTFACTORY // macro required in private section of implementation

public:
    ~BasicScriptFactory() noexcept override;

    AudioScript* spawn() override;

    const char* name() override;

    //const char* scriptInfo() override;

    void setupGUI(AudioScriptGUI& gui) override;
};

#endif // BASICSCRIPTFACTORY_H
