#ifndef AUDIOSETTINGS_H
#define AUDIOSETTINGS_H

#include "audioformat.h"
#include <QObject>

class AudioSettings : public QObject
{
    Q_OBJECT
public:
    explicit AudioSettings(QObject *parent = nullptr);

signals:

public slots:

private:
    AudioFormat m_format;
};

#endif // AUDIOSETTINGS_H
