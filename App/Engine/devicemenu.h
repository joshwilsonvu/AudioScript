#ifndef DEVICEMENU_H
#define DEVICEMENU_H

#include <QWidget>

class RtAudio;

class DeviceMenu : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceMenu(RtAudio& rtAudio, QWidget *parent = nullptr);

signals:
    void deviceChanged(unsigned int device);

public slots:

private:
    RtAudio& m_rtAudio;
    unsigned int m_currentDevice;
};

#endif // DEVICEMENU_H
