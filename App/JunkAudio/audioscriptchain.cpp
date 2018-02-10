#include "audioscriptchain.h"
#include "audioscriptbuffer.h"

AudioScriptChain::AudioScriptChain(AudioScript* script)
{
    add(script);
}

AudioScriptChain::~AudioScriptChain()
{
}

AudioScriptChain& AudioScriptChain::add(AudioScript* script)
{
    m_audioScript.push_back(script);
    return *this;
}

AudioScriptBuffer AudioScriptChain::process(AudioScriptBuffer input)
{
    for (AudioScript* script : m_audioScript) {
        input = script->process(input);
    }
    return input;
}

void AudioScriptChain::reset()
{
    for (AudioScript* script : m_audioScript) {
        script->reset();
    }
}
