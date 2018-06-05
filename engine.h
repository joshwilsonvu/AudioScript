#ifndef AS_ENGINE_H
#define AS_ENGINE_H

#include "globals.h"

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

namespace AS {

class Script;
class Buffer;
class Plugin;

class PluginLibrary;
class ProcessGraph;
class Processor;

class Engine
{
public:
    Engine();
    ~Engine();

    bool load(QString file);

    bool isLoaded(QString plugin);

    QString getInfo(QString plugin); // empty on fail

    void probeAudio();

    int numChannels() const;

    // TODO for starting out, I am going to make this start in mono duplex
    // mode, without any other options. Once the minimum viable product
    // is working, more options can be added and the interface can be smoothed.
    bool start();

    void stop();

private:    


    void initializeAudio();

    PluginLibrary* m_pluginLibrary;
    ProcessGraph* m_processGraph;
    Processor* m_processor;

};

} // AS

#endif // AS_ENGINE_H