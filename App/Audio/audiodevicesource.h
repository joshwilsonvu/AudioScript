#ifndef AUDIODEVICESOURCE_H
#define AUDIODEVICESOURCE_H

#include "globals.h"
#include "audioscriptbuffer.h"

#include <QIODevice>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioInput>

class InputBufferWrapper : public QIODevice
{
public:
    InputBufferWrapper(const QAudioFormat& format, QObject* parent);
    ~InputBufferWrapper();

    void open();
    void close() override;

    qint64 readData(char* data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

private:
    // hide inherited method
    bool open(OpenMode mode) override {}

    AudioScriptBuffer m_activeBuffer;

signals:
    void update();
};

class AudioDeviceSource
{
public:
    AudioDeviceSource(AS::BufferSize bufferSize);
    ~AudioDeviceSource();

    // closes any previously decoding file and opens a new one.
    bool open(QString target);

    // starts decoding of the previously opened file.
    void start();

    // pauses decoding of the previously opened file. start()
    // will resume decoding from the point left off.
    void stop();

    // releases all resources associated with decoding a file.
    // to be used again, the instance must be reopened.
    void close();

private:
    QAudioFormat m_format;
    AS::BufferSize m_bufferSize;
    QAudioDeviceInfo m_device;
    QAudioInput m_input;
};

#endif // AUDIODEVICESOURCE_H
