#include "audioscriptwrapper.h"

AudioScriptWrapper::AudioScriptWrapper(AudioScript* audioScript, AudioScriptLibrary* library)
    : m_audioScript(Q_NULLPTR), m_library(Q_NULLPTR)
{
    if (audioScript && library) {
        m_audioScript.reset(audioScript);
        m_library = library;
    }
}

AudioScriptWrapper::sample_t AudioScriptWrapper::process(AudioScriptWrapper::sample_t)
{

}

void AudioScriptWrapper::reset()
{

}
