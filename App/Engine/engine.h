#ifndef ENGINE_H
#define ENGINE_H

#include "plugin.h"
#include "audioscript.h"

#include <vector>
#include <memory>

class RtAudio;

class Engine
{
public:
    Engine();
    ~Engine();

    // same interface as AudioScript but no actual inheritance
    AudioScriptBuffer process(AudioScriptBuffer input);

    void probeAudio();

    int numChannels() const;

    // TODO for starting out, I am going to make this start in mono duplex
    // mode, without any other options. Once the minimum viable product
    // is working, more options can be added and the interface can be smoothed.
    bool start();

    void stop();

    int duplex(sample_t* outputBuffer, sample_t* inputBuffer,
                       unsigned int nBufferFrames, double streamTime,
                       unsigned long status);

private:
    void initializeAudio();

    std::unique_ptr<RtAudio> m_rtAudio;
    int m_numChannels;
    std::vector<AudioScript*> m_scripts;
};

#endif // ENGINE_H
