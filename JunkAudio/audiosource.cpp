#include "audiosource.h"
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioDecoder>
#include <QBuffer>
#include <QFile>

AudioSource::AudioSource(const QAudioFormat& format, QObject* parent)
    : QObject(parent),
      m_format(format),
      m_mode(AudioSource::None),
      m_decoder(nullptr),
      m_audioInput(nullptr),
      m_qbuffer(nullptr),
      m_buffer(0)
{
}

AudioSource::AudioSource(const QAudioFormat& format, QString targetFile,
                         QObject* parent)
    : AudioSource(format, parent)
{

}

/*
AudioSource::AudioSource(const AudioFormat& format,
                         const QAudioDeviceInfo& targetDevice, QObject* parent)
    : AudioSource(format, parent)

{
    open(targetDevice);
}
*/

AudioSource::~AudioSource()
{
}

/*
bool AudioSource::open(QString targetFile)
{
}
*/

/* TODO
bool AudioSource::open(QAudioDeviceInfo targetDevice)
{
    close();
    m_mode = AudioSource::Device;
    m_audioInput = new QAudioDeviceInfo(target);
}
*/

void AudioSource::start()
{
    // TODO
}

void AudioSource::stop()
{
    // TODO
}

void AudioSource::rewind()
{
    // TODO
}

void AudioSource::close()
{
    // TODO stop any processing currently happening
}

void AudioSource::setAudioFormat(const QAudioFormat& format)
{
    // TODO
}
