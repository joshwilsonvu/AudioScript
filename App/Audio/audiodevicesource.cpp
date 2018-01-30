#include "audiodevicesource.h"
#include "audioscriptutils.h"

InputBufferWrapper::InputBufferWrapper(const QAudioFormat& format, QObject* parent)
{
    // TODO support formats other than 32-bit float
    Q_ASSERT(format.sampleSize() == 8*sizeof(sample_t) && format.sampleType() == QAudioFormat::Float);
}

InputBufferWrapper::~InputBufferWrapper()
{

}

void InputBufferWrapper::start()
{
    QIODevice::open(QIODevice::WriteOnly);
}

void InputBufferWrapper::stop()
{
    QIODevice::close();
}

qint64 InputBufferWrapper::readData(char* data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)

    return 0;
}

qint64 InputBufferWrapper::writeData(const char* data, qint64 len)
{
    const sample_t* begin = reinterpret_cast<const sample_t*>(data);
    while (len > 0) {
        // std::copy()
    }
    return len;
}

AudioDeviceSource::AudioDeviceSource(AS::BufferSize bufferSize)
{

}
/*
m_format.setSampleRate(8000);
m_format.setChannelCount(1);
m_format.setSampleSize(16);
m_format.setSampleType(QAudioFormat::SignedInt);
m_format.setByteOrder(QAudioFormat::LittleEndian);
m_format.setCodec("audio/pcm");

QAudioDeviceInfo info(m_device);
if (!info.isFormatSupported(m_format)) {
    qWarning() << "Default format not supported - trying to use nearest";
    m_format = info.nearestFormat(m_format);
}

if (m_audioInfo)
    delete m_audioInfo;
m_audioInfo  = new AudioInfo(m_format, this);
connect(m_audioInfo, SIGNAL(update()), SLOT(refreshDisplay()));

createAudioInput();
*/
