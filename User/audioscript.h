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

    virtual sample_t process(sample_t sample);

    virtual QString name() const final;

// Protected methods: methods for use in derived classes
protected:
    void registerDouble(std::function<double (AudioScript*)> getter, std::function<void (AudioScript*, double)> setter, const std::string& name);
    void registerFloat(std::function<float (AudioScript*)> getter, std::function<void (AudioScript*, float)> setter, const std::string& name);
    void registerBool(std::function<bool (AudioScript*)> getter, std::function<void (AudioScript*, bool)> setter, const std::string& name);
    void registerInt(std::function<int (AudioScript*)> getter, std::function<void (AudioScript*, int)> setter, const std::string& name);


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

#endif // AUDIOSCRIPT_H
