
#include "CLASSNAME.hpp"

// Required function.
void* spawn() {
    return static_cast<AudioScript*>(new CLASSNAME());
}

// The constructor. Initialize your data fields here.
CLASSNAME::CLASSNAME() {
    // ex. registerDouble(&CLASSNAME::getGain, &CLASSNAME::setGain, "Gain");

}

// The destructor. Clean up any resources allocated here.
CLASSNAME::~CLASSNAME() {

}

// Apply this AudioScript to the range of samples provided.
sample_t CLASSNAME::process(sample_t sample) {

}

// Implement any helper functions your AudioScript uses.
