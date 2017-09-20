#include "audioscriptvariant.h"

AudioScriptVariant::AudioScriptVariant()
    : m_type(AudioScriptVariant::None),
      m_ptrToMember(Q_NULLPTR),
      m_name()
{
}

AudioScriptVariant::AudioScriptVariant(double AudioScript::*p_member, const std::string &name)
    : m_type(AudioScriptVariant::Double),
      m_ptrToMember(reinterpret_cast<unsigned char AudioScript::*>(p_member)),
      m_name(QString::fromStdString(name))
{
}

AudioScriptVariant::AudioScriptVariant(float AudioScript::*p_member, const std::string &name)
    : m_type(AudioScriptVariant::Float),
      m_ptrToMember(reinterpret_cast<unsigned char AudioScript::*>(p_member)),
      m_name(QString::fromStdString(name))
{
}

AudioScriptVariant::AudioScriptVariant(int AudioScript::*p_member, const std::string &name)
    : m_type(AudioScriptVariant::Int),
      m_ptrToMember(reinterpret_cast<unsigned char AudioScript::*>(p_member)),
      m_name(QString::fromStdString(name))
{
}

AudioScriptVariant::AudioScriptVariant(bool AudioScript::*p_member, const std::string &name)
    : m_type(AudioScriptVariant::Bool),
      m_ptrToMember(reinterpret_cast<unsigned char AudioScript::*>(p_member)),
      m_name(QString::fromStdString(name))
{
}

typename AudioScriptVariant::MemberType AudioScriptVariant::type() const
{
    return m_type;
}

QString AudioScriptVariant::name() const
{
    return m_name;
}

double* AudioScriptVariant::toDouble(AudioScript *audioScript)
{
    if (m_type == AudioScriptVariant::Double) {
        return &(audioScript->*reinterpret_cast<double AudioScript::*>
                 (m_ptrToMember));
    } else {
        return Q_NULLPTR;
    }
}

float* AudioScriptVariant::toFloat(AudioScript *audioScript)
{
    if (m_type == AudioScriptVariant::Float) {
        return &(audioScript->*reinterpret_cast<float AudioScript::*>
                 (m_ptrToMember));
    } else {
        return Q_NULLPTR;
    }
}

int* AudioScriptVariant::toInt(AudioScript *audioScript)
{
    if (m_type == AudioScriptVariant::Int) {
        return &(audioScript->*reinterpret_cast<int AudioScript::*>
                 (m_ptrToMember));
    } else {
        return Q_NULLPTR;
    }
}

bool* AudioScriptVariant::toBool(AudioScript *audioScript)
{
    if (m_type == AudioScriptVariant::Bool) {
        return &(audioScript->*reinterpret_cast<bool AudioScript::*>
                 (m_ptrToMember));
    } else {
        return Q_NULLPTR;
    }
}

