#ifndef AUDIOFORMAT_H
#define AUDIOFORMAT_H

#include "globals.h"

class QAudioFormat;

class ASUTILS_EXPORT AudioFormat
{
public:
    AudioFormat(AS::BufferSize bufferSize = AS::BufferSize::_256);
    AudioFormat(const QAudioFormat& format,
                AS::BufferSize bufferSize = AS::BufferSize::_256);

    QAudioFormat toQAudioFormat() const;

    AS::BufferSize bufferSize() const;
    void setBufferSize(AS::BufferSize bufferSize);

    int sampleRate() const;
    void setSampleRate(int sampleRate);

private:
    AS::BufferSize m_bufferSize;

    // TODO for minimum viable product, we are enforcing mono
    //int m_channelCount;

    int m_sampleRate;
};

#endif // AUDIOFORMAT_H
