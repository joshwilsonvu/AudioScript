#ifndef AUDIOSCRIPTUI_H
#define AUDIOSCRIPTUI_H

#include "globals.h"
#include "audioscript.h"
#include "audioscriptui_p.h"

namespace AS {

class ASUTILS_EXPORT AudioScriptUI
{

public:
    explicit AudioScriptUI();

    void addProperty(detail::Get<double> getter,
                     detail::Set<double> setter, std::string name);
    void addProperty(detail::Get<float> getter,
                     detail::Set<float> setter, std::string name);
    void addProperty(detail::Get<bool> getter,
                     detail::Set<bool> setter, std::string name);
    void addProperty(detail::Get<int> getter,
                     detail::Set<int> setter, std::string name);

    void show(AudioScript* script);



private:
    void addProperty(detail::Property&& property);
    QWidget* m_widget;
    QVector<detail::Property>* m_properties;

};

}

#endif // AUDIOSCRIPTUI_H
