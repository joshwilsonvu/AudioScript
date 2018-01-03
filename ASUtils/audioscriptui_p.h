#ifndef AUDIOSCRIPTUI_P_H
#define AUDIOSCRIPTUI_P_H

#include "audioscript.h"

class QWidget;
class QLabel;
class QDoubleSpinBox;
class QSpinBox;
class QCheckBox;

namespace AS {
namespace detail {

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
    MemberType type() const;
    // throw bad_variant_access if type does not match
    double getDouble(AudioScript* audioScript);
    void setDouble(AudioScript* audioScript, double value);
    float getFloat(AudioScript* audioScript);
    void setFloat(AudioScript* audioScript, float value);
    int getInt(AudioScript* audioScript);
    void setInt(AudioScript* audioScript, int value);
    bool getBool(AudioScript* audioScript);
    void setBool(AudioScript* audioScript, bool value);

    bool operator==(const Property& rhs) const;

    QLabel* label() const;

private:
    MemberType m_type;
    // generic type, cast as type() dictates
    Get<char>::MemFun m_get;
    Set<char>::MemFun m_set;

    QWidget* m_widget;
    QLabel* m_label;
    union {
        QDoubleSpinBox* m_DoubleSpinBox;
        QSpinBox* m_spinBox;
        QCheckBox* m_checkBox;
    };
};

} // detail
} // AS

#endif // AUDIOSCRIPTUI_P_H
