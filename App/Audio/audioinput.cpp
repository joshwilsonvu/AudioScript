#include "audioinput.h"

AudioInput::AudioInput(QObject *parent)
    : QObject(parent), m_inputMode(AudioInput::File)
{

}

AudioInput::InputMode AudioInput::mode() const
{
    return m_inputMode;
}

