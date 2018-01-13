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

    delete m_decoder;
    m_decoder = decoder;
    return true;
}

void AudioFileSource::start()
{

}

void AudioFileSource::stop()
{

}

void AudioFileSource::close()
{

}
