#include "audiodevicesource.h"

InputBufferWrapper::InputBufferWrapper(const QAudioFormat& format, QObject* parent)
{

}

InputBufferWrapper::~InputBufferWrapper()
{

}

void InputBufferWrapper::open()
{
    QIODevice::open(QIODevice::WriteOnly);
}

void InputBufferWrapper::close()
{
    QIODevice::close();
}

qint64 InputBufferWrapper::readData(char* data, qint64 maxlen)
{

}

qint64 InputBufferWrapper::writeData(const char* data, qint64 len)
{

}



AudioDeviceSource::AudioDeviceSource(AS::BufferSize bufferSize)
{

}


