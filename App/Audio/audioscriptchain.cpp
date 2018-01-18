#include "audioscriptchain.h"

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
