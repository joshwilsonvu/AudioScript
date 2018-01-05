#include "audioscriptutils.h"

#include <cmath>

// check if OpenCL would let you use DSP unit

sample_t AS::dB2amp(sample_t db)
{
    return std::pow(10., db / 20.);
}

sample_t AS::amp2dB(sample_t amp)
{
    return 20. * std::log10(std::abs(amp));
}

sample_t AS::clamp(sample_t x, sample_t low, sample_t high)
{
    return x < high ? (x < low ? low : x) : high;
}

sample_t AS::clamp(sample_t arg)
{
    return clamp(arg, -1., 1.);
}

// clamps x to [-1,1) and scales it up to the full integer range
int8_t AS::toInt8(sample_t x)
{
    x = clamp(x, -1., 1. + 1./INT8_MIN);
    return x * -double(INT8_MIN);
}

int16_t AS::toInt16(sample_t x)
{
    x = clamp(x, -1., 1. + 1./INT16_MIN);
    return x * -double(INT16_MIN);
}

int32_t AS::toInt24(sample_t x)
{
    x = clamp(x, -1., 1. + 8./INT32_MIN);
    return x * -double(INT32_MIN / 8);
}

int32_t AS::toInt32(sample_t x)
{
    x = clamp(x, -1., 1. + 1./INT32_MIN);
    return x * -double(INT32_MIN);
}

int64_t AS::toInt64(sample_t x)
{
    x = clamp(x, -1., 1. + 1./INT64_MIN);
    return x * -double(INT64_MIN);
}

// scales the full integer range of x down to [-1,1)
sample_t AS::fromInt8(int8_t x)
{
    sample_t d = sample_t(x);
    return d / -double(INT8_MIN);
}

sample_t AS::fromInt16(int16_t x)
{
    sample_t d = sample_t(x);
    return d / -double(INT16_MIN);
}

sample_t AS::fromInt24(int32_t x)
{
    sample_t d = sample_t(x);
    return d / -double(INT32_MIN / 8);
}

sample_t AS::fromInt32(int32_t x)
{
    sample_t d = sample_t(x);
    return d / -double(INT32_MIN);
}

sample_t AS::fromInt64(int64_t x)
{
    sample_t d = sample_t(x);
    return d / -double(INT64_MIN);
}
