#ifndef UTILS_H
#define UTILS_H

namespace AS {

// converts dBFS to positive linear amplitude (sample)
float dB2amp(float dB);

// converts linear amplitude (sample) to dBFS
float amp2dB(float amp);

// returns x clamped between low and high, inclusive
// Precondition: low <= high
float clamp(float x, float low, float high);

// returns x clamped between -1 and 1, inclusive
float clamp(float x);

}

#endif // UTILS_H
