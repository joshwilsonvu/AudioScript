#ifndef RTWRAPPER_H
#define RTWRAPPER_H

#include <QObject>

class AudioScriptException;
class RtAudio;

// enums in start() for input, output, duplex
// combine these with file input and output for a versatile solution

class RtWrapper : public QObject
{
    Q_OBJECT
public:

    RtWrapper(QObject *parent = nullptr);

    ~RtWrapper();

    enum Mode {
        Input,
        Output,
        Duplex
    };



signals:

public slots:
    bool start(Mode mode);

    void stop();

private:

    RtAudio* m_rtAudio;

};

#endif // RTWRAPPER_H
