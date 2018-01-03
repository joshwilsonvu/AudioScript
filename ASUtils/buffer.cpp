#include "buffer.h"
#include "bufferdata_p.h"
#include <algorithm>

namespace AS {

Buffer::Buffer(BufferSize size)
    : d(new BufferData(static_cast<int>(size)))
{
}

Buffer::Buffer(const Buffer &other)
    : d(other.d)
{
}

Buffer::Buffer(Buffer&& other)
    : d(std::move(other.d))
{
}

const Buffer& Buffer::operator=(const Buffer& other)
{
    d = other.d; // modifying one will not modify other
    return *this;
}

const Buffer& Buffer::operator=(Buffer&& other)
{
    d = std::move(other.d);
    return *this;
}

void Buffer::swap(Buffer &other)
{
    d.swap(other.d);
}

void Buffer::reset()
{
    fill(sample_t());
}

void Buffer::fill(sample_t value)
{
    std::fill(begin(), end(), value);
}

sample_t* Buffer::begin()
{
    return d->vec.data();
}

const sample_t* Buffer::begin() const
{
    return d->vec.data();
}

sample_t* Buffer::end()
{
    return begin() + (size_t)size();
}

const sample_t* Buffer::end() const
{
    return begin() + (size_t)size();
}

BufferSize Buffer::size() const
{
    return BufferSize(d->vec.size());
}


}
