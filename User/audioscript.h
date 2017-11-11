#ifndef AUDIOSCRIPT_H
#define AUDIOSCRIPT_H

//**********************
// AudioScript is the interface that effect classes will override and implement.
// It includes methods to return the effect's name, to process a sample, and
// optionally to show a custom dialog that allows the user to modify parameters.
// A default dialog is generated for the getter-setter pairs registered.
//**********************

// STL includes
#include <string>
#include <vector>

#include "audioscriptlibrary.h"
#include "audioscriptvariant.h"

class QString;
class AudioScriptEngine;

class AudioScript
{
// Public methods: only the methods required by the UI
public:

    AudioScript();
    virtual ~AudioScript();

    // floating point sample type
    typedef float sample_t;

    virtual sample_t process(sample_t sample);

    virtual QString name() const = 0;

    virtual void dialog(QWidget* );

// Protected methods: methods for use in derived classes
protected:
    void registerDouble(std::function<double (AudioScript*)> getter, std::function<void (AudioScript*, double)> setter, const std::string& name);
    void registerFloat(std::function<float (AudioScript*)> getter, std::function<void (AudioScript*, float)> setter, const std::string& name);
    void registerBool(std::function<bool (AudioScript*)> getter, std::function<void (AudioScript*, bool)> setter, const std::string& name);
    void registerInt(std::function<int (AudioScript*)> getter, std::function<void (AudioScript*, int)> setter, const std::string& name);
};

// tells meta-object system about interface
Q_DECLARE_INTERFACE(AudioScript, "com.VUSESolutions.AudioScript.AudioScript/1.0")

#endif // AUDIOSCRIPT_H
