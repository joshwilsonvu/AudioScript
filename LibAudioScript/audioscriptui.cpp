#include "audioscriptui.h"
#include <QWidget>

AudioScriptUI::AudioScriptUI()
{

}

void AudioScriptUI::addProperty(AudioScriptUI::DoubleGetter getter, AudioScriptUI::DoubleSetter setter, std::string name)
{
    (void)getter;
    (void)setter;
    (void)name;
}

void AudioScriptUI::addProperty(AudioScriptUI::FloatGetter getter, AudioScriptUI::FloatSetter setter, std::string name)
{
    (void)getter;
    (void)setter;
    (void)name;
}

void AudioScriptUI::addProperty(AudioScriptUI::BoolGetter getter, AudioScriptUI::BoolSetter setter, std::string name)
{
    (void)getter;
    (void)setter;
    (void)name;
}

void AudioScriptUI::addProperty(AudioScriptUI::IntGetter getter, AudioScriptUI::IntSetter setter, std::string name)
{
    (void)getter;
    (void)setter;
    (void)name;
}

void AudioScriptUI::show(AudioScript* script)
{
    (void)script;
}
