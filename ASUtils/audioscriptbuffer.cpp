#include "audioscriptbuffer.h"
#include "audioscriptexception.h"
#include "audioscriptutils.h"
#include <algorithm>

AudioScriptBuffer::AudioScriptBuffer(size_t size, bool zeroInitialize)
    : m_size(size),
      m_data(m_size ? (zeroInitialize ? new sample_t[m_size]()
                                      : new sample_t[m_size])
                    : nullptr)
{}

AudioScriptBuffer::AudioScriptBuffer(const AudioScriptBuffer& other)
    : AudioScriptBuffer(other.size(), false)
{
    // copy contents of other, no initial zero-fill
    std::copy(other.begin(), other.end(), begin());
}

AudioScriptBuffer::AudioScriptBuffer(AudioScriptBuffer&& other)
    : m_size(other.size()),
      m_data(other.m_data)
{
    // take and reset contents of other
    other.m_size = 0ul;
    other.m_data = nullptr;
}

AudioScriptBuffer::~AudioScriptBuffer() noexcept
{
    m_size = 0ul;
    delete[] m_data;
    m_data = nullptr;
}

AudioScriptBuffer& AudioScriptBuffer::operator=(const AudioScriptBuffer& other)
{
    // copy-and-swap idiom
    if (this != &other) {
        AS::assert(m_size == 0ul || m_size == other.m_size,
                   "AudioScriptBuffer: sizes mismatch.");
        AudioScriptBuffer temp(other);
        swap(temp);
    }
    return *this;
}

AudioScriptBuffer& AudioScriptBuffer::operator=(AudioScriptBuffer&& other)
{
    // move-and-swap idiom
    if (this != &other) {
        AS::assert(m_size == 0ul || m_size == other.m_size,
                   "AudioScriptBuffer: sizes mismatch.");
        AudioScriptBuffer temp(std::move(other));
        swap(temp);
    }
    return *this;
}

AudioScriptBuffer& AudioScriptBuffer::copy(const AudioScriptBuffer& other)
{
    operator=(other);
    return *this;
}

AudioScriptBuffer& AudioScriptBuffer::move(AudioScriptBuffer& other)
{
    operator=(std::move(other));
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

sample_t* AudioScriptBuffer::data() noexcept
{
    return m_data;
}

const sample_t* AudioScriptBuffer::data() const noexcept
{
    return m_data;
}

const sample_t* AudioScriptBuffer::constData() const noexcept
{
    return m_data;
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
    AS::assert(index < m_size, "AudioScriptBuffer: Invalid index");
    return m_data[index];
}

sample_t AudioScriptBuffer::at(size_t index) const
{
    return const_cast<AudioScriptBuffer*>(this)->at(index);
}
