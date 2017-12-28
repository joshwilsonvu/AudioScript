#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include <QIODevice>

class AudioInput : public QIODevice
{
    Q_OBJECT
public:

    enum InputMode {
        File
    }

    explicit AudioInput(QObject *parent = nullptr);

    InputMode mode() const;

    bool isReady() const;

    // true if mode() != File
    bool isSequential() const;
    void seek(qint64 pos);
    bool isLoopAvailable() const;
    bool isLooping() const;

    // only available if mode() == File
    void setLooping(bool loop);

    QString inputSource() const;



signals:
    // only emitted if mode() == File
    void finished(QString fileName);

public slots:

private:
    InputMode m_inputMode;
};

#endif // AUDIOINPUT_H
