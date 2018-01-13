#include "audioscriptbuffer.h"
#include <algorithm>

std::vector<AudioScriptBuffer> AudioScriptBuffer::deadBuffer;


AudioScriptBuffer::AudioScriptBuffer(AS::BufferSize bufferSize)
    : m_size(static_cast<size_t>(bufferSize)),
      m_data(new sample_t[m_size]()) // zero-initialized
{

}

AudioScriptBuffer::AudioScriptBuffer(const AudioFormat& format)
    : AudioScriptBuffer(format.bufferSize())
{
}

AudioScriptBuffer::AudioScriptBuffer(const AudioScriptBuffer& other)
    : m_size(other.m_size),
      m_data(new sample_t[m_size]()) // zero-initialized
{
    // copy contents of other
    std::copy(other.begin(), other.end(), begin());
}

AudioScriptBuffer::AudioScriptBuffer(AudioScriptBuffer&& other)
    : m_size(other.m_size),
      m_data(other.m_data)
{
    // take and reset contents of other
    other.m_size = 0ul;
    other.m_data = nullptr;
}

AudioScriptBuffer::~AudioScriptBuffer() noexcept
{
    // doesn't necessarily release resources, may be reused
    bury(std::move(*this));
}

AudioScriptBuffer& AudioScriptBuffer::operator=(AudioScriptBuffer other) noexcept
{
    // copy/move-and-swap idiom
    swap(other);
    return *this;
}

void AudioScriptBuffer::swap(AudioScriptBuffer &other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_data, other.m_data);
}

AudioScriptBuffer AudioScriptBuffer::clone() const
{
    // stack allocated clone
    return *this;
}

void AudioScriptBuffer::clear()
{
    fill(sample_t());
}

void AudioScriptBuffer::fill(sample_t value)
{
    std::fill(begin(), end(), value);
}

sample_t* AudioScriptBuffer::begin() noexcept
{
    return m_data;
}

const sample_t* AudioScriptBuffer::begin() const noexcept
{
    return m_data;
}

sample_t* AudioScriptBuffer::end() noexcept
{
    return m_data + m_size;
}

const sample_t* AudioScriptBuffer::end() const noexcept
{
    return m_data + m_size;
}

size_t AudioScriptBuffer::size() const noexcept
{
    return m_size;
}

sample_t& AudioScriptBuffer::operator[](size_t index)
{
    return m_data[index];
}

sample_t AudioScriptBuffer::operator[](size_t index) const
{
    return m_data[index];
}

sample_t& AudioScriptBuffer::at(size_t index)
{
    if (index >= m_size) {
        throw std::out_of_range("Invalid index.");
    }
    return m_data[index];
}

sample_t AudioScriptBuffer::at(size_t index) const
{
    if (index >= m_size) {
        throw std::out_of_range("Invalid index.");
    }
    return m_data[index];
}


void AudioScriptBuffer::releaseMemory()
{
    while (!deadBuffer.empty()) {
        deadBuffer.back().destroy();
        deadBuffer.pop_back();
    }
}

void AudioScriptBuffer::bury(AudioScriptBuffer&& buffer)
{
    if (buffer.m_data) {
        if (deadBuffer.size() < DEADBUFFER_CAPACITY) {
            // allocate once, subsequently no-op
            deadBuffer.reserve(DEADBUFFER_CAPACITY);
            deadBuffer.emplace_back(std::move(buffer));
        } else {
            buffer.destroy();
        }
    }
}

AudioScriptBuffer AudioScriptBuffer::resurrect(AS::BufferSize bufferSize)
{
    for (auto i = deadBuffer.rbegin(); i != deadBuffer.rend(); ++i) {
        // NOTE: we are currently only ressurecting if the requested sizes are
        // equal; we could use >= for better performance but wasted memory
        if (i->m_size == static_cast<size_t>(bufferSize)) {
            AudioScriptBuffer ret(std::move(*i));
            // access forward iterator from reverse
            deadBuffer.erase(i->base()-1);
            return ret;
        }
    }
    // must be handled in constructor, users should never see a size 0 buffer
    return AudioScriptBuffer();
}

AudioScriptBuffer::AudioScriptBuffer()
    : m_size(0),
      m_data(nullptr)
{
}

void AudioScriptBuffer::destroy()
{
    delete[] m_data;
    m_data = nullptr;
    m_size = 0ul;
}
