#include "audiofilesource.h"

AudioFileSource::AudioFileSource(AS::BufferSize bufferSize)
    : m_format(bufferSize), m_buffer(bufferSize)
{

}

AudioFileSource::~AudioFileSource()
{
    delete m_decoder;
}

bool AudioFileSource::open(QString target)
{
    // do nothing if file is already open
    if (m_decoder && m_decoder->sourceFilename() == target) {
        return true;
    }

    // check to see if we can even open the file
    QAudioDecoder* decoder = new QAudioDecoder();
    decoder.setSourceFilename(targetFile);
    if (decoder.error() != QAudioDecoder::NoError) {
        return false;
    }

    // try to get it into sample_t format, if not, no big deal
    QAudioFormat format = decoder.audioFormat();
    if (format.isValid() && format.sampleType() != QAudioFormat::Float) {
        format.setSampleType(QAudioFormat::Float);
        format.setSampleSize(sizeof(sample_t) * 8);
        decoder->setAudioFormat(format);
        if (decoder->error() == QAudioDecoder::FormatError) {
            // reset to original format, convert manually
            decoder->setAudioFormat(QAudioFormat());
        }
    }

    // stop any processing currently happening
    close();

    // move to the new decoder
    delete m_decoder;
    m_decoder = decoder;

    QObject::connect(m_decoder, SIGNAL(bufferReady()), [this] () {
        this->copyBuffer();
    });
    return true;
}

void AudioFileSource::start()
{
    m_decoder->start();
}

void AudioFileSource::stop()
{
    m_decoder->stop();
}

void AudioFileSource::close()
{

}

void AudioFileSource::copyBuffer()
{
    if (m_decoder && m_decoder->bufferAvailable()) {
        // make const to avoid unneccesary copying
        const QAudioBuffer qabuffer = m_decoder->read();
        qDebug() << "Got QAudioBuffer with " << qabuffer.frameCount() << "frames.";
    }
}
