#ifndef AS_PROCESSOR_H
#define AS_PROCESSOR_H

class RtAudio;

namespace AS {

class ProcessGraph;

class Processor
{
public:
    Processor(ProcessGraph* processGraph);

private:
    int duplex(sample_t* outputBuffer, sample_t* inputBuffer,
               unsigned int nBufferFrames, double streamTime,
               unsigned int status);

    std::unique_ptr<RtAudio> m_rtAudio;
    int m_numChannels;
};

}

#endif // AS_PROCESSOR_H
