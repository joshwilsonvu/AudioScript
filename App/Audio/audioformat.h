#ifndef AUDIOFORMAT_H
#define AUDIOFORMAT_H

#include "globals.h"

class QAudioFormat;

class AudioFormat
{
public:
    AudioFormat(AS::BufferSize bufferSize = AS::BufferSize::_256);
    AudioFormat(const QAudioFormat& format,
                AS::BufferSize bufferSize = AS::BufferSize::_256);

    QAudioFormat toQAudioFormat() const;

    AS::BufferSize bufferSize() const;
    void setBufferSize(AS::BufferSize bufferSize);

    int channelCount() const;
    void setChannelCount(int channelCount);

    int sampleRate() const;
    void setSampleRate(int sampleRate);

private:
    AS::BufferSize m_bufferSize;
    int m_channelCount;
    int m_sampleRate;
};

#endif // AUDIOFORMAT_H
