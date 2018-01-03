#include "bufferdata_p.h"

namespace AS {

BufferData::BufferData(size_t size)
    : vec(size)
{
}

BufferData::BufferData(const BufferData &other)
    : QSharedData(other), vec(other.vec)
{
}

BufferData::BufferData(BufferData &&other)
    : QSharedData(other), vec(std::move(other.vec))
{
}

BufferData::~BufferData()
{
}

}
