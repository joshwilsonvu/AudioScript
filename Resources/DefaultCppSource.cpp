
// Required function.
void* spawn() {
    return static_cast<AudioScript*>(new CLASSNAME());
}

// The constructor. Initialize your data fields here.
CLASSNAME::CLASSNAME() {

}

// The destructor. Clean up any resources allocated here.
CLASSNAME::~CLASSNAME() {

}

// Apply this AudioScript to the range of samples provided.
void CLASSNAME::process(std::vector<sample_t>& samples) {

}

// Implement any helper functions your AudioScript uses.
