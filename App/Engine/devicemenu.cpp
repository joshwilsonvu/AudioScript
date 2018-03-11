#include "devicemenu.h"

DeviceMenu::DeviceMenu(RtAudio& rtAudio, QWidget *parent)
    : QWidget(parent), m_rtAudio(rtAudio)
{
}
