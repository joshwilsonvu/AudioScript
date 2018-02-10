#ifndef RTWRAPPER_H
#define RTWRAPPER_H

#include <QObject>

class AudioScriptException;
class RtAudio;

// enums in contructor; for input, output, duplex
// combine these with file input and output for a versatile solution

class RtWrapper : public QObject
{
    Q_OBJECT
public:
    enum Mode {
        Input,
        Output,
        Duplex
    }
    RtWrapper(Mode mode, QObject *parent = nullptr)
    throw AudioScriptException;

    ~RtWrapper();

    void start();



signals:

public slots:

private:
    static int callback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                        double streamTime, RtAudioStreamStatus status, void *data );

    RtAudio* m_rtAudio;

};

#endif // RTWRAPPER_H
