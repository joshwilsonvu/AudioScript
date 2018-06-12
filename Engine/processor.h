#ifndef AS_PROCESSOR_H
#define AS_PROCESSOR_H

#include "3rdParty/RtAudio.h"
#include "processgraph.h"
#include "globals.h"

namespace AS {

class Buffer;
class ProcessGraph;

class Processor
{
public:
    Processor(ProcessGraph* processGraph);

    int numChannels() const;

    bool start();

    void stop();

    Buffer process(Buffer buffer);

    void probeAudio();

private:
    int duplex(sample_t* outputBuffer, sample_t* inputBuffer,
               unsigned int nBufferFrames, double streamTime,
               unsigned int status);

    static int duplex_callback(void* outputBuffer, void* inputBuffer,
                               unsigned int nBufferFrames, double streamTime,
                               unsigned int status, void* data);

    void initializeAudio();

    std::unique_ptr<RtAudio> m_rtAudio;
    std::unique_ptr<ProcessGraph> m_processGraph;
    int m_numChannels;
};

}

#endif // AS_PROCESSOR_H
