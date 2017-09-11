#include "audioscript.h"
#include "audioscriptengine.h"

AudioScript::AudioScript():m_library(nullptr), m_enabled(true) {}

// virtual
AudioScript::~AudioScript() {}

bool AudioScript::setParameter(const std::string &parameter, void *value) {
     // example code
     // SetParameter sp(parameter, value); // construct with parameter to set and value
     // return sp("foo", foo) || sp("bar", bar); // if passed "foo", sets foo to value, else go to bar
    (void)parameter, (void)value; // suppress unused parameter warning
    return false;
}

QString AudioScript::name() const {
    return m_library != nullptr ? m_library->name() : QString();
}

AudioScript::SetParameter::SetParameter(const std::string &param, const void *value)
    : m_param(param), m_value(value)
{}

bool AudioScript::isEnabled() const {
    return m_enabled;
}

void AudioScript::setEnabled(bool enabled) {
    m_enabled = enabled;
}

AudioScriptLibrary* AudioScript::getLibrary() {
    return m_library;
}

void AudioScript::setLibrary(AudioScriptLibrary* library) {
    m_library = library;
}
