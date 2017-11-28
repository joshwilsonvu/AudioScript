#include "basicscriptfactory.h"
#include "basicscript.h"
#include <iostream>

BasicScriptFactory::~BasicScriptFactory() noexcept
{

}

AudioScript* BasicScriptFactory::spawn()
{
    return new BasicScript();
}

const char* BasicScriptFactory::name()
{
    return "BS";
}

/*
const char* BasicScriptFactory::scriptInfo()
{
    return "A basic script, build alongside the host for debugging"
           "purposes. Its process method halves the volume of "
           "incoming samples.";
}
*/

void BasicScriptFactory::setupGUI(AudioScriptGUI& gui)
{
    Q_UNUSED(gui);
    std::cout << "GUI set up." << std::endl;
}
