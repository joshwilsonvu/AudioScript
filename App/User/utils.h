#ifndef UTILS_H
#define UTILS_H

#include "audioscript.h"
#include <cstdint>

namespace AS {

typedef typename AudioScript::sample_t sample_t;

// converts dBFS to positive linear amplitude (sample)
sample_t dB2amp(sample_t dB);

// converts linear amplitude (sample) to dBFS
sample_t amp2dB(sample_t amp);

// returns x clamped between low and high, inclusive
// Precondition: low <= high
sample_t clamp(sample_t x, sample_t low, sample_t high);

// returns x clamped between [-1 and 1, inclusive]
sample_t clamp(sample_t x);

// clamps x to [-1,1) and scales it up to the full integer range
int8_t toInt8(sample_t x);
int16_t toInt16(sample_t x);
int32_t toInt32(sample_t x);
int64_t toInt64(sample_t x);
// scales the full integer range of x down to [-1,1)
sample_t fromInt8(int8_t x);
sample_t fromInt16(int16_t x);
sample_t fromInt32(int32_t x);
sample_t fromInt64(int64_t x);

}

#endif // UTILS_H
