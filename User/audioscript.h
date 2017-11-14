#ifndef AUDIOSCRIPT_H
#define AUDIOSCRIPT_H

//**********************
// AudioScript is the interface that effect classes will override and implement.
// It includes methods to return the effect's name, to process a sample, and
// optionally to show a custom dialog that allows the user to modify parameters.
// A default dialog is generated for the getter-setter pairs registered.
//**********************


#include "audioscriptlibrary.h"
#include "audioscriptvariant.h"

//#define AS_ENABLE_DIALOG_METHOD
//#define AS_ENABLE_REGISTER_METHODS

class AudioScript
{
public:
    // floating point sample type, valid range [-1, 1]
    typedef float sample_t;

    virtual ~AudioScript() = 0;

    virtual sample_t process(sample_t sample) = 0;

    virtual void reset() = 0;

#ifdef AS_ENABLE_DIALOG_METHOD
    virtual void dialog(QWidget* parent);
#endif

#ifdef AS_ENABLE_REGISTER_METHODS
protected:
    void registerDouble(std::function<double (AudioScript*)> getter, std::function<void (AudioScript*, double)> setter, const std::string& name);
    void registerFloat(std::function<float (AudioScript*)> getter, std::function<void (AudioScript*, float)> setter, const std::string& name);
    void registerBool(std::function<bool (AudioScript*)> getter, std::function<void (AudioScript*, bool)> setter, const std::string& name);
    void registerInt(std::function<int (AudioScript*)> getter, std::function<void (AudioScript*, int)> setter, const std::string& name);
#endif

};

// tells meta-object system about interface
Q_DECLARE_INTERFACE(AudioScript, "com.VUSESolutions.AudioScript.AudioScript/1.0")

#endif // AUDIOSCRIPT_H
