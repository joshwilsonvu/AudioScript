#include "buffer.h"
#include "exception.h"
#include "utils.h"
#include <algorithm>

namespace AS {

Buffer::Buffer(size_t size, bool zeroInitialize)
    : m_size(size),
      m_data(m_size ? (zeroInitialize ? new sample_t[m_size]()
                                      : new sample_t[m_size])
                    : nullptr)
{}

Buffer::Buffer(size_t size, sample_t* data)
    : m_size(size),
      m_data(data)
{
}

Buffer::Buffer(const Buffer& other)
    : Buffer(other.size(), false)
{
    // copy contents of other, no initial zero-fill
    std::copy(other.begin(), other.end(), begin());
}

Buffer::Buffer(Buffer&& other)
    : m_size(other.size()),
      m_data(other.m_data)
{
    // take and reset contents of other
    other.m_size = 0ul;
    other.m_data = nullptr;
}

Buffer::~Buffer() noexcept
{
    m_size = 0ul;
    delete[] m_data;
    m_data = nullptr;
}

Buffer& Buffer::operator=(const Buffer& other)
{
    // copy-and-swap idiom
    if (this != &other) {
        AS::check(m_size == 0ul || m_size == other.m_size,
                   "Buffer: sizes mismatch.");
        Buffer temp(other);
        swap(temp);
    }
    return *this;
}

Buffer& Buffer::operator=(Buffer&& other)
{
    // move-and-swap idiom
    if (this != &other) {
        AS::check(m_size == 0ul || m_size == other.m_size,
                   "Buffer: sizes mismatch.");
        swap(other);
    }
    return *this;
}

Buffer& Buffer::copyAssign(const Buffer& other)
{
    operator=(other);
    return *this;
}

Buffer& Buffer::moveAssign(Buffer& other)
{
    operator=(std::move(other));
    return *this;
}

void Buffer::swap(Buffer &other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_data, other.m_data);
}

Buffer Buffer::clone() const
{
    // stack allocated clone
    return *this;
}

void Buffer::clear()
{
    fill(sample_t());
}

void Buffer::fill(sample_t value)
{
    std::fill(begin(), end(), value);
}

sample_t* Buffer::data() noexcept
{
    return m_data;
}

const sample_t* Buffer::data() const noexcept
{
    return m_data;
}

const sample_t* Buffer::constData() const noexcept
{
    return m_data;
}

sample_t* Buffer::begin() noexcept
{
    return m_data;
}

const sample_t* Buffer::begin() const noexcept
{
    return m_data;
}

sample_t* Buffer::end() noexcept
{
    return m_data + m_size;
}

const sample_t* Buffer::end() const noexcept
{
    return m_data + m_size;
}

size_t Buffer::size() const noexcept
{
    return m_size;
}

sample_t& Buffer::operator[](size_t index)
{
    return m_data[index];
}

sample_t Buffer::operator[](size_t index) const
{
    return m_data[index];
}

sample_t& Buffer::at(size_t index)
{
    AS::check(index < m_size, "Buffer: Invalid index");
    return m_data[index];
}

sample_t Buffer::at(size_t index) const
{
    return const_cast<Buffer*>(this)->at(index);
}

Buffer::PairProxy Buffer::operator&(const Buffer& other)
{
    return PairProxy(*this, other);
}

Buffer::PairProxy::PairProxy(const Buffer& first, const Buffer& second)
    : first(first), second(second) {}

} // AS
