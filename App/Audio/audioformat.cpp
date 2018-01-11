#include "audioformat.h"

#include <QFile>
#include <QAudioDeviceInfo>
#include <QAudioFormat>

AudioFormat::AudioFormat(AS::BufferSize bufferSize)
    : m_bufferSize(bufferSize)
{
}

AudioFormat::AudioFormat(const QAudioFormat& format, AS::BufferSize bufferSize)
    : m_bufferSize(bufferSize),
      m_channelCount(format.channelCount()),
      m_sampleRate(format.sampleRate())
{
}

QAudioFormat AudioFormat::toQAudioFormat() const
{
    QAudioFormat format;
    format.setChannelCount(channelCount());
    format.setSampleRate(sampleRate());
    format.setSampleSize(sizeof(sample_t) * 8);
    format.setSampleType(QAudioFormat::Float);
    return format;
}

int AudioFormat::sampleRate() const
{
    return m_sampleRate;
}

void AudioFormat::setSampleRate(int sampleRate)
{
    m_sampleRate = sampleRate;
}

int AudioFormat::channelCount() const
{
    return m_channelCount;
}

void AudioFormat::setChannelCount(int channelCount)
{
    m_channelCount = channelCount;
}

AS::BufferSize AudioFormat::bufferSize() const
{
    return m_bufferSize;
}

void AudioFormat::setBufferSize(AS::BufferSize bufferSize)
{
    m_bufferSize = bufferSize;
}
