#include "audioinput.h"
#include <QScopedPointer>

AudioInput::AudioInput(AudioInput::InputMode mode, QObject* parent)
    : QObject(parent), m_mode(mode), m_file(nullptr), m_decoder(nullptr)
{
    switch(m_mode) {
    case AudioInput::File:
        m_file = new QFile(this);
        m_decoder = new QAudioDecoder(this);
        connect(m_decoder, SIGNAL(finished()), this, SLOT(stop()));
        break;
    default:
        return;
    }
}

AudioInput::~AudioInput()
{
}

bool AudioInput::open(QString target)
{
    QScopedPointer<QAudioDecoder> tempDecoder;
    QScopedPointer<QFile> tempFile;
    switch(mode()) {
    case AudioInput::File:
        tempFile.reset(new QFile(target));
        if (!tempFile->exists()) {
            return false;
        }
        tempDecoder.reset(new QAudioDecoder());
        tempDecoder->setSourceFilename(target);
        // TODO check for better methods to detect availability with
        // specified audio format
        if (tempDecoder->error() != QAudioDecoder::NoError) {
            return false;
        }
        delete m_decoder;
        m_decoder = tempDecoder.take();
        delete m_file;
        m_file = tempFile.take();
        break;
    default:
        return false;
    }
    m_target = target;
    return true;
}

AudioInput::InputMode AudioInput::mode() const
{
    return m_mode;
}

QString AudioInput::target() const
{
    return m_target;
}

void AudioInput::start()
{
    //TODO
    switch(m_mode) {
    case File:
        m_decoder->start();

        break;
    case Device:

        break;
    }
}

void AudioInput::stop()
{
    //TODO
    switch(m_mode) {
    case File:
        m_decoder->stop();

        break;
    case Device:

        break;
    }
}
