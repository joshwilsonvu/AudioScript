#ifndef AUDIOSCRIPTUTILS_H
#define AUDIOSCRIPTUTILS_H

#include "globals.h"
#include <cstdint>

namespace AS {

// terminates the audio processing if the condition is not true
void Assert(bool cond, const char* message = nullptr);

// converts dBFS to positive linear amplitude (sample)
ASUTILS_EXPORT sample_t dB2amp(sample_t dB);

// converts linear amplitude (sample) to dBFS
ASUTILS_EXPORT sample_t amp2dB(sample_t amp);

// returns x clamped between low and high, inclusive
// Precondition: low <= high
ASUTILS_EXPORT sample_t clamp(sample_t x, sample_t low, sample_t high);

// returns x clamped between [-1 and 1, inclusive]
ASUTILS_EXPORT sample_t clamp(sample_t x);

// clamps x to [-1,1) and scales it up to the full integer range
ASUTILS_EXPORT int8_t toInt8(sample_t x);
ASUTILS_EXPORT int16_t toInt16(sample_t x);
ASUTILS_EXPORT int32_t toInt24(sample_t x);
ASUTILS_EXPORT int32_t toInt32(sample_t x);
ASUTILS_EXPORT int64_t toInt64(sample_t x);
ASUTILS_EXPORT uint8_t toUint8(sample_t x);
ASUTILS_EXPORT uint16_t toUint16(sample_t x);
ASUTILS_EXPORT uint32_t toUint24(sample_t x);
ASUTILS_EXPORT uint32_t toUint32(sample_t x);
ASUTILS_EXPORT uint64_t toUint64(sample_t x);
// scales the full integer range of x down to [-1,1)
ASUTILS_EXPORT sample_t fromInt8(int8_t x);
ASUTILS_EXPORT sample_t fromInt16(int16_t x);
ASUTILS_EXPORT sample_t fromInt24(int32_t x);
ASUTILS_EXPORT sample_t fromInt32(int32_t x);
ASUTILS_EXPORT sample_t fromInt64(int64_t x);
ASUTILS_EXPORT sample_t fromUint8(uint8_t x);
ASUTILS_EXPORT sample_t fromUint16(uint16_t x);
ASUTILS_EXPORT sample_t fromUint24(uint32_t x);
ASUTILS_EXPORT sample_t fromUint32(uint32_t x);
ASUTILS_EXPORT sample_t fromUint64(uint64_t x);

}

#endif // AUDIOSCRIPTUTILS_H
