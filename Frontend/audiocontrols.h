#ifndef AUDIOCONTROLS_H
#define AUDIOCONTROLS_H

#include <QWidget>

class QGroupBox;
class QToolButton;

// Graphical user interface that contains controls to play, pause, and otherwise
// control audio processing and playback.
class AudioControls : public QWidget
{
    Q_OBJECT

public:
    AudioControls(QWidget* parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
    virtual ~AudioControls();

public slots:


private:
    QToolButton* m_play_b;
    QToolButton* m_pause_b;
    QGroupBox* m_groupBox;
};

#endif // AUDIOCONTROLS_H
