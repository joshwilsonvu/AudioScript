#include "audiosettings.h"
#include <QAudioFormat>
#include <QAudioDeviceInfo>

AudioSettings::AudioSettings(QObject *parent)
    : QObject(parent),
      m_format(QAudioDeviceInfo::defaultOutputDevice().preferredFormat())
{
}
