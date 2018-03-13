#ifndef AUDIOSCRIPTLOG_H
#define AUDIOSCRIPTLOG_H

#include <QObject>

class AudioScriptLog : public QObject
{
    Q_OBJECT

public:
    // This class shall replace std::cout for plugins, and all information
    // streamed to this will be displayed in the AudioScript application.
    // A proxy may be used.
    // One stream chain (logger << x << y << z;) should be added atomically
    // to the stream.
    // The stream should be flushed to the display *at most* once per
    // processed buffer, to reduce I/O to manageable levels, and not in the
    // audio thread.
    AudioScriptLog(QObject* parent = nullptr);
    ~AudioScriptLog() override;
};

#endif // AUDIOSCRIPTLOG_H
