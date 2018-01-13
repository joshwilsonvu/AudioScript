#include "audiosource.h"
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioDecoder>
#include <QBuffer>
#include <QFile>

AudioSource::AudioSource(const AudioFormat& format, QObject* parent)
    : QObject(parent),
      m_format(format),
      m_mode(AudioSource::None),
      m_decoder(nullptr),
      m_audioInput(nullptr),
      m_qbuffer(nullptr),
      m_buffer(static_cast<size_t>(m_format.bufferSize()))
{
}

AudioSource::AudioSource(const AudioFormat& format, QString targetFile,
                         QObject* parent)
    : AudioSource(format, parent)
{
    open(targetFile);
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

bool AudioSource::open(QString targetFile)
{
    close();
    m_mode = AudioSource::File;
    m_fileSource = new AudioFileSource(m_format.bufferSize());
    return m_fileSource->open(targetFile);
}

/*
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
    switch(m_mode) {
    case None:
        break;
    case Device:
        break;
    case File:
        m_decoder->stop();
    }
}

void AudioSource::rewind()
{
    switch(m_mode) {
    case None:
        break;
    case Device:
        break;
    case File:
        m_decoder->stop();
        m_decoder->setSourceFilename(m_decoder->sourceFilename());
    }
}

void AudioSource::close()
{
    // stop any processing currently happening
    stop();
    switch(m_mode) {
    case None:
        break;
    case Device:
        delete m_audioInput;
        delete m_qbuffer;
        m_audioInput = nullptr;
        m_qbuffer = nullptr;
    case File:
        delete m_decoder;
        m_decoder = nullptr;
    }
    m_mode = None;
}

void AudioSource::setAudioFormat(const AudioFormat& format)
{
    // TODO
}
