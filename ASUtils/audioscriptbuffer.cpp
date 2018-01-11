#include "audioscriptbuffer.h"
#include <algorithm>

AudioScriptBuffer::AudioScriptBuffer(size_t size)
    : m_size(size),
      m_data(m_size ? new sample_t[m_size] : nullptr)
{
}

AudioScriptBuffer::AudioScriptBuffer(const AudioScriptBuffer& other)
    : AudioScriptBuffer(other.m_size)
{
    // copy contents of other
    std::copy(other.begin(), other.end(), begin());
}

AudioScriptBuffer::AudioScriptBuffer(AudioScriptBuffer&& other)
    : m_size(other.m_size), m_data(other.m_data)
{
    // take and reset contents of other
    other.m_size = 0ul;
    other.m_data = nullptr;
}

AudioScriptBuffer::~AudioScriptBuffer() noexcept
{
    delete[] m_data;
    m_data = nullptr;
    m_size = 0ul;
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
