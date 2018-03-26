#ifndef AUDIOSCRIPTPROPERTY_H
#define AUDIOSCRIPTPROPERTY_H

template <typename T>
class AudioScriptProperty
{
public:
    AudioScriptProperty();

    T& operator= (const T& v) {
        return value = v;
    }

    operator const T& ()
private:
    T m_value;
    std::function<void(const T&)> m_onSet;
};

#endif // AUDIOSCRIPTPROPERTY_H
