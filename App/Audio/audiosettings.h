#ifndef AUDIOSETTINGS_H
#define AUDIOSETTINGS_H

#include <QObject>
#include <QAudioFormat>

class AudioSettings : public QObject
{
    Q_OBJECT
public:
    explicit AudioSettings(QObject *parent = nullptr);

signals:

public slots:

private:
    QAudioFormat m_format;
};

#endif // AUDIOSETTINGS_H
