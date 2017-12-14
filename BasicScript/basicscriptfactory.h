#ifndef BASICSCRIPTFACTORY_H
#define BASICSCRIPTFACTORY_H

#include "audioscriptfactory.h"
#include "audioscriptui.h"

class BasicScriptFactory : public QObject, public AudioScriptFactory
{
    AUDIOSCRIPTFACTORY // macro required in private section of implementation

public:
    ~BasicScriptFactory() noexcept override;

    AudioScript* spawn() override;

    const char* name() override;

    //const char* scriptInfo() override;

    //void setupGUI(AudioScriptUI& gui) override;
};

#endif // BASICSCRIPTFACTORY_H
