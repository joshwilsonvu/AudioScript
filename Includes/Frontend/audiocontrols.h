#ifndef AUDIOCONTROLS_H
#define AUDIOCONTROLS_H

#include "sidewidgetbase.h"

// Graphical user interface that contains controls to play, pause, and otherwise
// control audio processing and playback.
class AudioControls : public SideWidgetBase
{
    Q_OBJECT

public:
    AudioControls(QWidget* parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
    virtual ~AudioControls();

private:

};

#endif // AUDIOCONTROLS_H
