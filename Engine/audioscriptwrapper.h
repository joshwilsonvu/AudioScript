#ifndef AUDIOSCRIPTWRAPPER_H
#define AUDIOSCRIPTWRAPPER_H

#include <memory>

#include "audioscript.h"
#include "audioscriptlibrary.h"

class AudioScriptWrapper
{
public:
    AudioScriptWrapper(AudioScript* audioScript, AudioScriptLibrary* library);

    typedef typename AudioScript::sample_t sample_t;

    sample_t process(sample_t);

    void reset();

    QString name() const;

    //bool has_vector_process();

private:
    std::unique_ptr<AudioScript> m_audioScript;
    AudioScriptLibrary* m_library;
};

#endif // AUDIOSCRIPTWRAPPER_H
