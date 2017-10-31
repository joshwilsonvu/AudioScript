#include "audioscript.h"
#include "audioscriptengine.h"

AudioScript::AudioScript()
    : m_library(Q_NULLPTR), m_enabled(true) {}

// virtual
AudioScript::~AudioScript() {}

// virtual
sample_t AudioScript::process(sample_t sample)
{
    return sample;
}

/*
bool AudioScript::setParameter(const std::string &parameter, void *value) {
     // example code
     // SetParameter sp(parameter, value); // construct with parameter to set and value
     // return sp("foo", foo) || sp("bar", bar); // if passed "foo", sets foo to value, else go to bar
    (void)parameter, (void)value; // suppress unused parameter warning
    return false;
}*/

QString AudioScript::name() const {
    return m_library != Q_NULLPTR ? m_library->name() : QString();
}

/*
AudioScript::SetParameter::SetParameter(const std::string &param, const void *value)
    : m_param(param), m_value(value)
{}
*/

bool AudioScript::isEnabled() const {
    return m_enabled;
}

void AudioScript::setEnabled(bool enabled) {
    m_enabled = enabled;
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
