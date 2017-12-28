#include <QWidget>
#include <QVector>
#include "audioscriptui.h"


namespace AS {

AudioScriptUI::AudioScriptUI()
    : m_properties(new QVector<detail::Property>())
{
}

void AudioScriptUI::addProperty(detail::Get<double> getter, detail::Set<double> setter, std::string name)
{
    detail::Property temp(getter.f, setter.f, QString::fromStdString(name));
    addProperty(temp);
}

void AudioScriptUI::addProperty(detail::Get<float> getter, detail::Set<float> setter, std::string name)
{
    detail::Property temp(getter.f, setter.f, QString::fromStdString(name));
    addProperty(temp);
}

void AudioScriptUI::addProperty(detail::Get<bool> getter, detail::Set<bool> setter, std::string name)
{
    detail::Property temp(getter.f, setter.f, QString::fromStdString(name));
    addProperty(temp);
}

void AudioScriptUI::addProperty(detail::Get<int> getter, detail::Set<int> setter, std::string name)
{
    detail::Property temp(getter.f, setter.f, QString::fromStdString(name));
    addProperty(temp);
}



void AudioScriptUI::show(AudioScript* script)
{
    (void)script;
}

// private method that finishes adding the Property object
void AudioScriptUI::addProperty(detail::Property property) {
    if (!m_properties->contains(temp)) {

        m_properties->append(temp);
        temp = detail::Property();
    }
}

detail::Property::Property()
    : m_widget(Q_NULLPTR), m_type(detail::Property::Int)
{
}

detail::Property::Property(detail::Get<double>::MemFun get, detail::Set<double>::MemFun set, QString name)
    : Property(), m_type(detail::Property::Double)
{

}
// TODO etc...

bool detail::Property::operator=(const detail::Property& rhs) const
{
    return m_type == rhs.m_type && m_get == rhs.m_get && m_set == rhs.m_set;
}

}
