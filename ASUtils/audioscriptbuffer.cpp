#include "audioscriptbuffer.h"
#include "bufferdata_p.h"
#include <algorithm>

namespace AS {

AudioScriptBuffer::AudioScriptBuffer(BufferSize size)
    : d(new BufferData(static_cast<int>(size)))
{
}

AudioScriptBuffer::AudioScriptBuffer(const AudioScriptBuffer &other)
    : d(other.d)
{
}

AudioScriptBuffer::AudioScriptBuffer(AudioScriptBuffer&& other)
    : d(std::move(other.d))
{
}

const AudioScriptBuffer& AudioScriptBuffer::operator=(const AudioScriptBuffer& other)
{
    d = other.d; // modifying one will not modify other
    return *this;
}

const AudioScriptBuffer& AudioScriptBuffer::operator=(AudioScriptBuffer&& other)
{
    d = std::move(other.d);
    return *this;
}

void AudioScriptBuffer::swap(AudioScriptBuffer &other)
{
    d.swap(other.d);
}

void AudioScriptBuffer::reset()
{
    fill(sample_t());
}

void AudioScriptBuffer::fill(sample_t value)
{
    std::fill(begin(), end(), value);
}

sample_t* AudioScriptBuffer::begin()
{
    return d->vec.data();
}

const sample_t* AudioScriptBuffer::begin() const
{
    return d->vec.data();
}

sample_t* AudioScriptBuffer::end()
{
    return begin() + (size_t)size();
}

const sample_t* AudioScriptBuffer::end() const
{
    return begin() + (size_t)size();
}

BufferSize AudioScriptBuffer::size() const
{
    return BufferSize(d->vec.size());
}


}
