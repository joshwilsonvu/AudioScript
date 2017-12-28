#ifndef AUDIOSCRIPTGUI_H
#define AUDIOSCRIPTGUI_H

#include "globals.h"
#include "audioscript.h"

class QWidget;
class QLabel;
class QDoubleSpinBox;
class QSpinBox;
class QCheckBox;

namespace AS {
namespace detail {

/* Allows for
struct Sub : public AudioScript
{
    ~Sub() override = default;
    sample_t process(sample_t sample) override { return 2 * sample; }
    void reset() override {}
    double get() { return 5; }
    void set(double) {}
};
AudioScriptVariant v(&Sub::get, &Sub::set); // *Note implicit, safe casting!*
 */

template<typename T>
struct Get {
    typedef T (AudioScript::*MemFun) (void);
    MemFun f;

    template <typename U> Get(T (U::*subMemFun) (void)) { // implicit cast
        static_assert(std::is_base_of<AudioScript, U>::value,
                          "Method not a member of a subclass of AudioScript.");
        f = static_cast<MemFun>(subMemFun);
    }

    Get(T (AudioScript::*memFun) (void)) : f(memFun) {}
};
template<typename T>
struct Set {
    typedef void (AudioScript::*MemFun) (T);
    MemFun f;

    template <typename U> Set(void (U::*subMemFun) (T)) { // implicit cast
        static_assert(std::is_base_of<AudioScript, U>::value,
                          "Method not a member of a subclass of AudioScript.");
        f = static_cast<MemFun>(subMemFun);
    }

    Set(void (AudioScript::*memFun) (T)) : f(memFun) {}
};

class Property {
public:
    Property(); // null property
    Property(Get<double>::MemFun g, Set<double>::MemFun s, QString name);
    Property(Get<float>::MemFun g, Set<float>::MemFun s, QString name);
    Property(Get<bool>::MemFun g, Set<bool>::MemFun s, QString name);
    Property(Get<int>::MemFun g, Set<int>::MemFun s, QString name);

    enum MemberType {
        Double,
        Float,
        Int,
        Bool
    };
    // throw bad_variant_access if type does not match
    double getDouble(AudioScript* audioScript);
    void setDouble(AudioScript* audioScript, double value);
    float getFloat(AudioScript* audioScript);
    void setFloat(AudioScript* audioScript, float value);
    int getInt(AudioScript* audioScript);
    void setInt(AudioScript* audioScript, int value);
    bool getBool(AudioScript* audioScript);
    void setBool(AudioScript* audioScript, bool value);

    bool operator=(const Property& rhs) const;

public:
    Get<void>::MemFun m_get;
    Set<void>::MemFun m_set;

    QLabel* m_label;
    union {
        QDoubleSpinBox* m_DoubleSpinBox;
        QSpinBox* m_spinBox;
        QCheckBox* m_checkBox;
    };

    const MemberType m_type;
};

} // detail

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

#endif // AUDIOSCRIPTGUI_H
