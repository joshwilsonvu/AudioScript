#include "audioscriptvariant.h"

const char* bad_variant_access::what() const noexcept {
    return "Mismatched type for AudioScriptVariant access.";
}

bad_variant_access::~bad_variant_access() {}

AudioScriptVariant::AudioScriptVariant()
    : m_type(AudioScriptVariant::None),
      m_getter(nullptr),
      m_setter(nullptr)
{
}

AudioScriptVariant::AudioScriptVariant(std::function<double (AudioScript*)> getter,
                                       std::function<void (AudioScript*, double)> setter)
    : m_type(AudioScriptVariant::Double),
      m_getter((GenericGetter)getter),
      m_setter((GenericSetter)setter)
{
}

AudioScriptVariant::AudioScriptVariant(std::function<float (AudioScript*)> getter,
                                       std::function<void (AudioScript*, float)> setter)
    : m_type(AudioScriptVariant::Float),
      m_getter((GenericGetter)getter),
      m_setter((GenericSetter)setter)
{
}

AudioScriptVariant::AudioScriptVariant(std::function<bool (AudioScript*)> getter,
                                       std::function<void (AudioScript*, bool)> setter)
    : m_type(AudioScriptVariant::Bool),
      m_getter((GenericGetter)getter),
      m_setter((GenericSetter)setter)
{
}

AudioScriptVariant::AudioScriptVariant(std::function<int (AudioScript*)> getter,
                                       std::function<void (AudioScript*, int)> setter)
    : m_type(AudioScriptVariant::Int),
      m_getter((GenericGetter)getter),
      m_setter((GenericSetter)setter)
{
}

typename AudioScriptVariant::MemberType AudioScriptVariant::type() const
{
    return m_type;
}

double AudioScriptVariant::getDouble(AudioScript *audioScript)
{
    if (m_type == AudioScriptVariant::Double) {
        return ((DoubleGetter)m_getter)(audioScript);
    } else {
        throw bad_variant_access();
    }
}

void AudioScriptVariant::setDouble(AudioScript *audioScript, double value)
{
    if (m_type == AudioScriptVariant::Double) {
        ((DoubleSetter)m_setter)(audioScript, value);
    } else {
        throw bad_variant_access();
    }
}

float AudioScriptVariant::getFloat(AudioScript *audioScript)
{
    if (m_type == AudioScriptVariant::Float) {
        return ((FloatGetter)m_getter)(audioScript);
    } else {
        throw bad_variant_access();
    }
}

void AudioScriptVariant::setFloat(AudioScript *audioScript, float value)
{
    if (m_type == AudioScriptVariant::Float) {
        ((FloatSetter)m_setter)(audioScript, value);
    } else {
        throw bad_variant_access();
    }
}

int AudioScriptVariant::getInt(AudioScript *audioScript)
{
    if (m_type == AudioScriptVariant::Int) {
        return ((IntGetter)m_getter)(audioScript);
    } else {
        throw bad_variant_access();
    }
}

void AudioScriptVariant::setBool(AudioScript *audioScript, bool value)
{
    if (m_type == AudioScriptVariant::Bool) {
        ((BoolSetter)m_setter)(audioScript, value);
    } else {
        throw bad_variant_access();
    }
}

bool AudioScriptVariant::getBool(AudioScript *audioScript)
{
    if (m_type == AudioScriptVariant::Bool) {
        return ((BoolGetter)m_getter)(audioScript);
    } else {
        throw bad_variant_access();
    }
}

void AudioScriptVariant::setInt(AudioScript *audioScript, int value)
{
    if (m_type == AudioScriptVariant::Int) {
        ((IntSetter)m_setter)(audioScript, value);
    } else {
        throw bad_variant_access();
    }
}
