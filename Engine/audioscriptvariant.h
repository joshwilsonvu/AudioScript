#ifndef AUDIOSCRIPTVARIANT_H
#define AUDIOSCRIPTVARIANT_H

#include <functional>
#include <exception>
#include "audioscript.h"

class bad_variant_access : public std::exception
{
public:
    virtual const char* what() const noexcept override;
    virtual ~bad_variant_access();
};



// Marshals registered parameters, enabling GUI interfaces to change values
// in real time.
class AudioScriptVariant
{
public:

    AudioScriptVariant();
    AudioScriptVariant(detail::Getter<double> getter,
                       detail::Setter<double> setter);
    AudioScriptVariant(detail::Getter<float> getter,
                       detail::Setter<float> setter);
    AudioScriptVariant(detail::Getter<int> getter,
                       detail::Setter<int> setter);
    AudioScriptVariant(detail::Getter<bool> getter,
                       detail::Setter<bool> setter);

    enum MemberType {
        Double,
        Float,
        Int,
        Bool,
        None
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

private:
    MemberType m_type;
    detail::Getter<void> m_getter;
    detail::Setter<void> m_setter;
};

#endif // AUDIOSCRIPTVARIANT_H
