#include "utils.h"
#include "exception.h"

#include <cmath>

// check if OpenCL would let you use DSP unit

namespace AS {

void Assert(bool cond, const char* message)
{
    if (!cond) {
        throw Exception(message);
    }
}

sample_t dB2amp(sample_t db)
{
    return std::pow(10., db / 20.);
}

sample_t amp2dB(sample_t amp)
{
    return 20. * std::log10(std::abs(amp));
}

sample_t clamp(sample_t x, sample_t low, sample_t high)
{
    return x < high ? (x < low ? low : x) : high;
}

sample_t clamp(sample_t arg)
{
    return clamp(arg, -1., 1.);
}

// clamps x to [-1,1) and scales it up to the full integer range
int8_t toInt8(sample_t x)
{
    x = clamp(x, -1., 1. + 1./INT8_MIN);
    return x * -double(INT8_MIN);
}

int16_t toInt16(sample_t x)
{
    x = clamp(x, -1., 1. + 1./INT16_MIN);
    return x * -double(INT16_MIN);
}

int32_t toInt24(sample_t x)
{
    x = clamp(x, -1., 1. + 8./INT32_MIN);
    return x * -double(INT32_MIN / 8);
}

int32_t toInt32(sample_t x)
{
    x = clamp(x, -1., 1. + 1./INT32_MIN);
    return x * -double(INT32_MIN);
}

int64_t toInt64(sample_t x)
{
    x = clamp(x, -1., 1. + 1./INT64_MIN);
    return x * -double(INT64_MIN);
}

uint8_t toUint8(sample_t x)
{
    return toInt8(x)-INT8_MIN;
}

uint16_t toUint16(sample_t x)
{
    return toInt16(x)-INT16_MIN;
}

uint32_t toUint24(sample_t x)
{
    return toInt24(x)-INT32_MIN/8;
}

uint32_t toUint32(sample_t x)
{
    return toInt24(x)-INT32_MIN;
}

uint64_t toUint64(sample_t x)
{
    return toInt64(x)-INT64_MIN;
}

// scales the full integer range of x down to [-1,1)
sample_t fromInt8(int8_t x)
{
    sample_t d = sample_t(x);
    return d / -double(INT8_MIN);
}

sample_t fromInt16(int16_t x)
{
    sample_t d = sample_t(x);
    return d / -double(INT16_MIN);
}

sample_t fromInt24(int32_t x)
{
    sample_t d = sample_t(x);
    return d / -double(INT32_MIN / 8);
}

sample_t fromInt32(int32_t x)
{
    sample_t d = sample_t(x);
    return d / -double(INT32_MIN);
}

sample_t fromInt64(int64_t x)
{
    sample_t d = sample_t(x);
    return d / -double(INT64_MIN);
}

sample_t fromUint8(uint8_t x)
{
    return fromInt8(x+INT8_MIN);
}

sample_t fromUint16(uint16_t x)
{
    return fromInt16(x+INT16_MIN);
}

sample_t fromUint24(uint32_t x)
{
    return fromInt24(x+INT32_MIN/8);
}

sample_t fromUint32(uint32_t x)
{
    return fromInt32(x+INT32_MIN);
}

sample_t fromUint64(uint64_t x)
{
    return fromInt64(x+INT64_MIN);
}

}
