
/*
 * Copyright 2017
 * The following declares the functions that will be called within your code.
 * Subclass the given class and implement the functions as described.
 */

#include <audioscript.h>

/* Required function. */
extern "C" void* spawn();
/**********************/

// Subclass AudioScript
class CLASSNAME : public AudioScript
{
public:
    // The constructor. Initialize your data fields here.
    CLASSNAME();

    // The destructor. Clean up any resources allocated here.
    ~CLASSNAME();

    // Apply this AudioScript to the range of samples provided.
    void process(std::vector<sample_t>& samples) override;

protected:
    // Declare any helper functions your AudioScript uses.

private:
    // Declare the data fields your AudioScript uses. For example,
    // double gain;

};
