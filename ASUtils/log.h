#ifndef AS_LOG_H
#define AS_LOG_H

#include <QDebug>

// TODO: Create a true logging class, with a thread safe proxy,
// an internal buffer, and a way for the engine to extract its contents.

// This class shall replace std::cout for plugins, and all information
// streamed to this will be displayed in the AudioScript application.
// A proxy may be used.
// One stream chain (logger << x << y << z;) should be added atomically
// to the stream.
// The stream should be flushed to the display *at most* once per
// processed buffer, to reduce I/O to manageable levels, and not in the
// audio thread.

namespace AS {

using Log = QDebug;

Log log();

void setLogDestination(QIODevice* out);

} // AS

#endif // AS_LOG_H
