#include <QString>
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
    addProperty(std::move(temp));
}

void AudioScriptUI::addProperty(detail::Get<float> getter, detail::Set<float> setter, std::string name)
{
    detail::Property temp(getter.f, setter.f, QString::fromStdString(name));
    addProperty(std::move(temp));
}

void AudioScriptUI::addProperty(detail::Get<bool> getter, detail::Set<bool> setter, std::string name)
{
    detail::Property temp(getter.f, setter.f, QString::fromStdString(name));
    addProperty(std::move(temp));
}

void AudioScriptUI::addProperty(detail::Get<int> getter, detail::Set<int> setter, std::string name)
{
    detail::Property temp(getter.f, setter.f, QString::fromStdString(name));
    addProperty(std::move(temp));
}



void AudioScriptUI::show(AudioScript* script)
{
    (void)script;
}

// private method that finishes adding the Property object
void AudioScriptUI::addProperty(detail::Property&& property) {
    if (!m_properties->contains(property)) {
        m_properties->append(property);
    }
}

}
