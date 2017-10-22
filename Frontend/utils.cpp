#include "utils.h"

#include <cmath>

// check if OpenCL would let you use DSP unit

float db2amp(float db)
{
    return std::pow(10.0f, db / 20.0f);
}

float amp2db(float amp)
{
    return 20.0f * std::log10(std::abs(amp));
}

float clamp(float x, float low, float high)
{
    return x < high ? (x < low ? low : x) : high;
}

float clamp(float arg)
{
    return clamp(arg, -1.0f, 1.0f);
}

