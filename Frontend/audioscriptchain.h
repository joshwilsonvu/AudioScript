#ifndef AUDIOSCRIPTCHAIN_H
#define AUDIOSCRIPTCHAIN_H

#include "sidewidgetbase.h"

// The graphical interface for users to control the order are parameters of
// the AudioScripts that are applied to incoming audio.
class AudioScriptChain : public SideWidgetBase
{
    Q_OBJECT

public:
    AudioScriptChain(QWidget* parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
    virtual ~AudioScriptChain();

private:

};

#endif // AUDIOSCRIPTCHAIN_H
