#include "audioscriptbuffer.h"
#include <algorithm>
#include <vector>

// define the following symbol to disable the bury/resurrect
// optimization that reduces the overhead of new/delete operations
//#define NO_RESURRECT

size_t AudioScriptBuffer::m_size = 256ul;
int AudioScriptBuffer::m_count = 0;

#ifndef NO_RESURRECT
// local to this file
namespace {
constexpr const size_t DEADBUFFER_CAPACITY = 10ul;
std::vector<AudioScriptBuffer::value_type*> deadBuffer;
}
#endif

AudioScriptBuffer::AudioScriptBuffer(bool zeroInitialize)
{
#ifndef NO_RESURRECT
    if (resurrect()) {
        // we got a dead buffer of the size we needed, members are set
        if (zeroInitialize) {
            clear(); // zero-filled
        }
    } else {
#endif
        if (zeroInitialize) {
            m_data = new sample_t[m_size](); // zero-filled
        } else {
            m_data = new sample_t[m_size];
        }
#ifndef NO_RESURRECT
    }
#endif
}

AudioScriptBuffer::AudioScriptBuffer(const AudioScriptBuffer& other)
    : AudioScriptBuffer(false)
{
    // copy contents of other, no initial zero-fill
    std::copy(other.begin(), other.end(), begin());
}

AudioScriptBuffer::AudioScriptBuffer(AudioScriptBuffer&& other)
    : m_data(other.m_data)
{
    // take and reset contents of other
    other.m_data = nullptr;
}

AudioScriptBuffer::~AudioScriptBuffer() noexcept
{
#ifndef NO_RESURRECT
    // doesn't necessarily release resources, may be reused
    if (m_data) {
        bury();
    }
#else
    destroy();
#endif
}

AudioScriptBuffer& AudioScriptBuffer::operator=(AudioScriptBuffer other) noexcept
{
    // copy/move-and-swap idiom
    swap(other);
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
    if (index >= m_size) {
        throw std::out_of_range("Invalid index.");
    }
    return m_data[index];
}

sample_t AudioScriptBuffer::at(size_t index) const
{
    return const_cast<AudioScriptBuffer*>(this)->at(index);
}

void AudioScriptBuffer::releaseMemory()
{
#ifndef NO_RESURRECT
    while (!deadBuffer.empty()) {
        delete[] deadBuffer.back();
        deadBuffer.pop_back();
    }
    deadBuffer.shrink_to_fit();
#endif
}

void AudioScriptBuffer::bury()
{
#ifndef NO_RESURRECT
    // precondition: m_data
    if (deadBuffer.size() < DEADBUFFER_CAPACITY) {
        // allocate once, subsequently no-op
        deadBuffer.reserve(DEADBUFFER_CAPACITY);
        deadBuffer.push_back(m_data);
        m_data = nullptr;
    } else {
#endif
        destroy();
#ifndef NO_RESURRECT
    }
#endif
    // postcondition: *this guaranteed to hold no resources
}

bool AudioScriptBuffer::resurrect()
{
#ifndef NO_RESURRECT
    // precondition: !m_data, should only be called in constructor
    if (!m_data && !deadBuffer.empty()) {
        m_data = deadBuffer.back();
        deadBuffer.pop_back();
        return true;
    }
#endif
    return false;
}

void AudioScriptBuffer::destroy()
{
    delete[] m_data;
    m_data = nullptr;
}
