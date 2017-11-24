#ifndef AUDIOSCRIPT_H
#define AUDIOSCRIPT_H

//**********************
// AudioScript is the interface that effect classes will override and implement.
// It includes methods to return the effect's name, to process a sample, and
// optionally to show a custom dialog that allows the user to modify parameters.
// A default dialog is generated for the getter-setter pairs registered.
//**********************

class AudioScript
{
public:
    // floating point sample type, valid range [-1, 1]
    typedef float sample_t;

    virtual ~AudioScript() = default;

    virtual sample_t process(sample_t sample) = 0;

    virtual void reset() = 0;

};

// tells meta-object system about interface
//Q_DECLARE_INTERFACE(AudioScript, "AudioScript")

#endif // AUDIOSCRIPT_H
