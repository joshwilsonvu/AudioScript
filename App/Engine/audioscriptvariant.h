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
struct Getter {
    typedef T (AudioScript::*baseMemFun) (void);

    template <typename U>
    Getter(T (U::*subMemFun) (void)) { // implicit cast
        static_assert(std::is_base_of<AudioScript, U>::value,
                          "Function not a member of a subclass of AudioScript.");
        f = static_cast<baseMemFun>(subMemFun);
    }

    baseMemFun f;
};
template<typename T>
struct Setter {
    typedef void (AudioScript::*baseMemFun) (T);

    template <typename U>
    Setter(void (U::*subMemFun) (T)) { // implicit cast
        static_assert(std::is_base_of<AudioScript, U>::value,
                          "Function not a member of a subclass of AudioScript.");
        f = static_cast<baseMemFun>(subMemFun);
    }

    baseMemFun f;
};

} // detail

// Marshals registered parameters, enabling GUI interfaces to change values
// in real time.
class AudioScriptVariant
{
private:
    template <typename T>
    struct helper {
        typedef std::function<T(AudioScript*)> getter;
        typedef std::function<void(AudioScript*,T)> setter;
    };
public:
    typedef helper<unsigned char>::getter GenericGetter;
    typedef helper<unsigned char>::setter GenericSetter;
    typedef helper<double>::getter DoubleGetter;
    typedef helper<double>::setter DoubleSetter;
    typedef helper<float>::getter FloatGetter;
    typedef helper<float>::setter FloatSetter;
    typedef helper<bool>::getter BoolGetter;
    typedef helper<bool>::setter BoolSetter;
    typedef helper<int>::getter IntGetter;
    typedef helper<int>::setter IntSetter;

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
    GenericGetter m_getter;
    GenericSetter m_setter;
};

#endif // AUDIOSCRIPTVARIANT_H
