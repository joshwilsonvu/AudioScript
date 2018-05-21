#ifndef ENGINE_H
#define ENGINE_H

#include "plugin.h"
#include "audioscript.h"

#include <vector>
#include <memory>

/**
 * The AudioScript Engine class should expose its own API and be fully
 * self-contained, much like RtAudio. The API will enable all audio-related
 * functionality, such as spawning scripts, recording and playing audio,
 * converting to AudioScriptBuffers, and running the processing chain in a
 * separate, high-priority or realtime thread.
 *
 * During execution, std::cout will be redirected to a std::ostringstream,
 * whose contents are accessible via an API method. SCRATCH THIS, mutable
 * global state. Use dependency injection with a stream instead.
 *
 * Usage will most likely be building and linking to a library and including
 * the engine.h header file.
 */

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
