#include "basicscriptfactory.h"
#include "basicscript.h"
#include <iostream>

BasicScriptFactory::~BasicScriptFactory() noexcept {}

AudioScript* BasicScriptFactory::spawn()
{
    return new BasicScript();
}

const char* BasicScriptFactory::name()
{
    return "BasicScript";
}

void BasicScriptFactory::setupGUI(AudioScriptGUI& gui)
{
    (void)gui;
    std::cout << "GUI set up." << std::endl;
}
