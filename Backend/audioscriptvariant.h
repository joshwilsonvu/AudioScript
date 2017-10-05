#ifndef AUDIOSCRIPTVARIANT_H
#define AUDIOSCRIPTVARIANT_H

#include <functional>
#include <exception>

class bad_variant_access : public std::exception
{
public:
    virtual const char* what() const noexcept override;
    virtual ~bad_variant_access();
};

class AudioScript;

// Marshals registered parameters, enabling GUI interfaces to change values
// in real time.
class AudioScriptVariant
{
private:
    typedef std::function<unsigned char(AudioScript*)> GenericGetter;
    typedef std::function<void(AudioScript*, unsigned char)> GenericSetter;
    typedef std::function<double(AudioScript*)> DoubleGetter;
    typedef std::function<void(AudioScript*, double)> DoubleSetter;
    typedef std::function<float(AudioScript*)> FloatGetter;
    typedef std::function<void(AudioScript*, float)> FloatSetter;
    typedef std::function<bool(AudioScript*)> BoolGetter;
    typedef std::function<void(AudioScript*, bool)> BoolSetter;
    typedef std::function<int(AudioScript*)> IntGetter;
    typedef std::function<void(AudioScript*, int)> IntSetter;
public:
    AudioScriptVariant();
    AudioScriptVariant(DoubleGetter getter,
                       DoubleSetter setter);
    AudioScriptVariant(FloatGetter getter,
                       FloatSetter setter);
    AudioScriptVariant(BoolGetter getter,
                       BoolSetter setter);
    AudioScriptVariant(IntGetter getter,
                       IntSetter setter);

    enum MemberType {
        Double,
        Float,
        Int,
        Bool,
        None
    };
    MemberType type() const;

    // throw bad type() does not match
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
