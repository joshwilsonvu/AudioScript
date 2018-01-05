#ifndef AUDIOSCRIPTBUFFER_H
#define AUDIOSCRIPTBUFFER_H

#include "globals.h"
#include <QSharedDataPointer>

#include "bufferdata_p.h"

class ASUTILS_EXPORT AudioScriptBuffer
{
public:

    AudioScriptBuffer(size_t size);
    AudioScriptBuffer(const AudioScriptBuffer& other);
    AudioScriptBuffer(AudioScriptBuffer&& other);
    const AudioScriptBuffer& operator=(const AudioScriptBuffer& other);
    const AudioScriptBuffer& operator=(AudioScriptBuffer&& other);

    void swap(AudioScriptBuffer& other);

    void reset();
    void fill(sample_t value);

    sample_t* begin();
    const sample_t* begin() const;
    sample_t* end();
    const sample_t* end() const;

    BufferSize size() const;

private:
    // Implicit sharing
    QSharedDataPointer<AudioScriptBufferData> d;
};

#endif // AUDIOSCRIPTBUFFER_H
