#ifndef AUDIOSCRIPT_H
#define AUDIOSCRIPT_H

// STL includes
#include <string>
#include <vector>

#include "audioscriptlibrary.h"
#include "audioscriptvariant.h"

class QString;
class AudioScriptEngine;

// floating point sample type
typedef float sample_t;

class AudioScript
{
// Public methods: only the methods required by the UI
public:
    AudioScript();
    virtual ~AudioScript();

    virtual void process(std::vector<sample_t>& samples) = 0;
    virtual bool setParameter(const std::string& parameter, void* value);

    QString name() const;

// Protected methods: methods for use in derived classes
protected:
    /*
     * example code for setParameter(parameter, value) {
     *     SetParameter sp(parameter, value); // construct with parameter to set and value
     *     return sp("foo", foo) || sp("bar", bar); // if passed "foo", sets foo to value, else go to bar
     * }

    class SetParameter {
    public:
        SetParameter(const std::string& param, const void* value);
        template <typename T>
        bool operator() (const std::string& fieldName, T& field);
    private:
        const std::string& m_param;
        const void* m_value;
    };
    */

    // need name of AudioScript, name of member, pointer to member, type of member
    template <typename Derived>
    void registerMember(double Derived::* d_member, const std::string& name);
    template <typename Derived>
    void registerMember(float Derived::* f_member, const std::string& name);
    template <typename Derived>
    void registerMember(bool Derived::* b_member, const std::string& name);
    template <typename Derived>
    void registerMember(int Derived::* i_member, const std::string& name);

// Private methods: only used in base class or by friend classes, not derived classes
private:
    // allow AudioScriptEngine/Library to access the following methods
    friend class AudioScriptEngine;
    friend class AudioScriptLibrary;
    AudioScriptLibrary* getLibrary();
    void setLibrary(AudioScriptLibrary* library);
    bool isEnabled() const;
    void setEnabled(bool enabled);

    AudioScriptLibrary* m_library; // non-owning
    bool m_enabled;
};

/*
template <typename T>
bool AudioScript::SetParameter::operator() (const std::string& fieldName, T& field)
{
    if (m_value && m_param == fieldName) {
        field = *reinterpret_cast<const T*>(m_value);
        return true;
    }
    return false;
}
*/

template <typename Derived>
void AudioScript::registerMember(double Derived::* d_member, const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(static_cast<double AudioScript::*>(d_member), name));
}

template <typename Derived>
void AudioScript::registerMember(float Derived::* f_member, const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(static_cast<float AudioScript::*>(f_member), name));
}

template <typename Derived>
void AudioScript::registerMember(bool Derived::* b_member, const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(static_cast<bool AudioScript::*>(b_member), name));
}

template <typename Derived>
void AudioScript::registerMember(int Derived::* i_member, const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(static_cast<int AudioScript::*>(i_member), name));
}

#endif // AUDIOSCRIPT_H
