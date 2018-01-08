#include <QString>
#include <QVector>
#include "audioscriptui.h"


AudioScriptUI::AudioScriptUI()
    : m_properties(new QVector<AudioScriptUI::Property>())
{
}

void AudioScriptUI::addProperty(AudioScriptUI::Get<double> getter, AudioScriptUI::Set<double> setter, const char* name)
{
    Property temp(getter.f, setter.f, QString::fromStdString(name));
    addProperty(std::move(temp));
}

void AudioScriptUI::addProperty(AudioScriptUI::Get<float> getter, AudioScriptUI::Set<float> setter, const char* name)
{
    Property temp(getter.f, setter.f, QString::fromStdString(name));
    addProperty(std::move(temp));
}

void AudioScriptUI::addProperty(AudioScriptUI::Get<bool> getter, AudioScriptUI::Set<bool> setter, const char* name)
{
    Property temp(getter.f, setter.f, QString::fromStdString(name));
    addProperty(std::move(temp));
}

void AudioScriptUI::addProperty(AudioScriptUI::Get<int> getter, AudioScriptUI::Set<int> setter, const char* name)
{
    Property temp(getter.f, setter.f, QString::fromStdString(name));
    addProperty(std::move(temp));
}



void AudioScriptUI::show(AudioScript* script)
{
    (void)script;
}

// private method that finishes adding the Property object
void AudioScriptUI::addProperty(AudioScriptUI::Property&& property) {
    if (!m_properties->contains(property)) {
        m_properties->append(property);
    }
}

AudioScriptUI::Property::Property()
    : m_widget(Q_NULLPTR), m_type(Property::Int)
{
}

AudioScriptUI::Property::Property(Get<double>::MemFun get, Set<double>::MemFun set, QString name)
    : m_type(Property::Double),
      m_get(reinterpret_cast<decltype(m_get)>(get)),
      m_set(reinterpret_cast<decltype(m_set)>(set))
{

}

AudioScriptUI::Property::Property(Get<float>::MemFun get, Set<float>::MemFun set, QString name)
    : m_type(Property::Float),
      m_get(reinterpret_cast<decltype(m_get)>(get)),
      m_set(reinterpret_cast<decltype(m_set)>(set))
{

}

AudioScriptUI::Property::Property(Get<bool>::MemFun get, Set<bool>::MemFun set, QString name)
    : m_type(Property::Bool),
      m_get(reinterpret_cast<decltype(m_get)>(get)),
      m_set(reinterpret_cast<decltype(m_set)>(set))
{

}

AudioScriptUI::Property::Property(Get<int>::MemFun get, Set<int>::MemFun set, QString name)
    : m_type(Property::Int),
      m_get(reinterpret_cast<decltype(m_get)>(get)),
      m_set(reinterpret_cast<decltype(m_set)>(set))
{

}

typename AudioScriptUI::Property::MemberType AudioScriptUI::Property::type() const
{
    return m_type;
}

bool AudioScriptUI::Property::operator==(const Property& rhs) const
{
    return m_type == rhs.m_type && m_get == rhs.m_get && m_set == rhs.m_set;
}
