#include "audiosettings.h"
#include <QAudioDeviceInfo>
#include <QIODevice>

AudioSettings::AudioSettings(QObject *parent)
    : QObject(parent)
{
    m_format = QAudioDeviceInfo::defaultOutputDevice().preferredFormat();
}
