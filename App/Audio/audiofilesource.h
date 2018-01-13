#ifndef AUDIOFILESOURCE_H
#define AUDIOFILESOURCE_H

#include "globals.h"
#include "audioformat.h"
#include "audioscriptbuffer.h"

#include <QAudioDecoder>

class AudioFileSource
{
public:
    AudioFileSource(AS::BufferSize bufferSize);
    ~AudioFileSource();

    // closes any previously decoding file and opens a new one.
    bool open(QString target);

    // starts decoding of the previously opened file.
    void start();

    // pauses decoding of the previously opened file. start()
    // will resume decoding from the point left off.
    void stop();

    // releases all resources associated with decoding a file.
    // to be used again, the instance must be reopened.
    void close();

private:
    // lets the class decode audio files, converts output
    QAudioDecoder* m_decoder;

    AudioFormat m_format;

    AudioScriptBuffer m_buffer;
};

#endif // AUDIOFILESOURCE_H
