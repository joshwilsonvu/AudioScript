#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

// The way to do this is not to subclass QIODevice but to
// make a class with a QAudioInput and a QBuffer member
// and start the reading with something like
//   m_audioInput.start(&m_qbuffer);
// and subsequently copy the filled buffer to the active
// AudioScriptBuffer with
//   std::copy(m_qbuffer.begin(), m_qbuffer.end(), m_buffer.begin());
// For file decoding, respond to QAudioDecoder's bufferReady() signal
// or check with bufferAvailable() and call read(). Copy the
// returned QAudioBuffer to the active AudioScriptBuffer with
//   if (qabuffer.isValid()) {
//       std::copy(qabuffer.constData<sample_t>(),
//           qabuffer.constData<sample_t>() + qabuffer.sampleCount(),
//           m_buffer.begin());
//   }

// TODO - separate the members and functionality for each mode into
//     seperate classes. Then, either use a tagged union of pointers to
//     each of these classes or enforce a common interface and use an
//     interface pointer and virtual calls.

#include "audioformat.h"
#include "audioscriptbuffer.h"

#include <QObject>

class QAudioDecoder;
class QAudioInput;
class QBuffer;

class AudioSource : public QObject
{
    Q_OBJECT
public:
    AudioSource(const AudioFormat& format, QObject* parent = 0);
    AudioSource(const AudioFormat& format, QString targetFile,
                QObject* parent = 0);
    //AudioSource(const AudioFormat& format,
    //            const QAudioDeviceInfo& targetDevice, QObject* parent = 0);

    ~AudioSource();

    bool open(QString targetFile);
    //bool open(QAudioDeviceInfo targetDevice);

    bool bufferAvailable() const;
    AudioScriptBuffer buffer();

    AudioFormat format() const;

    // Device members
    //static QList<QAudioDeviceInfo> availableDevices();

public slots:
    void start();
    void stop();
    void rewind();
    void close();
    void setAudioFormat(const AudioFormat& format);

signals:
    void bufferReady();

private:

    enum InputMode {
        None  = 0,
        File = 1,
        Device = 2
    };

    AudioFormat m_format;

    // Invariant: if m_mode == File, the File InputMode members
    // will be valid and all other member pointers will be nullptr,
    // same for other modes
    InputMode m_mode;

    // File InputMode members
    QAudioDecoder* m_decoder;

    // Device InputMode members
    QAudioInput* m_audioInput;
    QBuffer* m_qbuffer; // QIODevice for QAudioInput.start()

    AudioScriptBuffer m_buffer;

};

#endif // AUDIOSOURCE_H
