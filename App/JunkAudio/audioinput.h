#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include <QObject>
#include <QStringList>
#include <QFile>
#include <QAudioDeviceInfo> // for getting raw realtime input
#include <QAudioDecoder> // for decoding files



// In pull mode, the
/*
class IOHelper : public QIODevice
{
    Q_OBJECT
public:
    qint64 writeData(const char *data, qint64 len) override;
};
*/

class AudioInput : public QObject
{
    Q_OBJECT
public:
    enum InputMode {
        File,
        Device
    };

    AudioInput(InputMode mode, QObject *parent = nullptr);
    ~AudioInput();

    bool open(QString target);

    InputMode mode() const;

    QString target() const;

signals:
    // only emitted if mode() == File
    //void finished(QString fileName);

    void bufferReady(AudioInput*);

public slots:
    void start();
    void stop();

private:
    InputMode m_mode;

    QAudioFormat m_format;

    QString m_target;

    // file-based members; only initialized in File mode
    QFile* m_file;
    QAudioDecoder* m_decoder;

    // device-based members; only initialized in Device mode

};

#endif // AUDIOINPUT_H
