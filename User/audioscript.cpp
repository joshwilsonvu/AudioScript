#include "audioscript.h"
#include "audioscriptengine.h"

AudioScript::AudioScript()
    : m_library(Q_NULLPTR), m_enabled(true) {}

AudioScript::~AudioScript() {}

sample_t AudioScript::process(sample_t sample)
{
    return sample;
}

AudioScriptLibrary* AudioScript::getLibrary() {
    return m_library;
}

// called by spawning library immediately after construction
void AudioScript::setLibrary(AudioScriptLibrary* library) {
    m_library = library;
}


void AudioScript::registerDouble(std::function<double(AudioScript*)> getter,
                                 std::function<void(AudioScript*, double)> setter,
                                 const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(getter, setter), name);
}

void AudioScript::registerFloat(std::function<float(AudioScript*)> getter,
                                std::function<void(AudioScript*, float)> setter,
                                const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(getter, setter), name);
}
void AudioScript::registerBool(std::function<bool(AudioScript*)> getter,
                               std::function<void(AudioScript*, bool)> setter,
                               const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(getter, setter), name);
}
void AudioScript::registerInt(std::function<int(AudioScript*)> getter,
                              std::function<void(AudioScript*, int)> setter,
                              const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(getter, setter), name);
}
