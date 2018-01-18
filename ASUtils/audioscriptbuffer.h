#ifndef AUDIOSCRIPTBUFFER_H
#define AUDIOSCRIPTBUFFER_H

#include "globals.h"

class ASUTILS_EXPORT AudioScriptBuffer
{
public:
    typedef sample_t value_type;

    // Constructors and destructor
    AudioScriptBuffer(bool zeroInitialize = true);
    AudioScriptBuffer(const AudioScriptBuffer& other);
    AudioScriptBuffer(AudioScriptBuffer&& other);
    ~AudioScriptBuffer() noexcept;

    // unified assignment operator
    AudioScriptBuffer& operator=(AudioScriptBuffer other) noexcept;

    // explicit copy/move methods
    AudioScriptBuffer& copy(const AudioScriptBuffer& other);
    AudioScriptBuffer& move(AudioScriptBuffer& other);
    void swap(AudioScriptBuffer& other) noexcept;

    // convienience function to create a copy
    AudioScriptBuffer clone() const;

    // pointwise modifying
    void clear();
    void fill(sample_t value);

    // iterators
    sample_t* data() noexcept; // same as begin()
    const sample_t* data() const noexcept;
    const sample_t* constData() const noexcept;
    sample_t* begin() noexcept;
    const sample_t* begin() const noexcept;
    sample_t* end() noexcept;
    const sample_t* end() const noexcept;
    size_t size() const noexcept;

    // Accessors
    sample_t& operator[] (size_t index);
    sample_t operator[] (size_t index) const;
    sample_t& at(size_t index);
    sample_t at(size_t index) const;

    // TODO Element-wise operators
    // AudioScriptBuffer& operator*=(sample_t x);
    // AudioScriptBuffer& operator*=(const AudioScriptBuffer& other);
    // ...

    // Equivalent to std::transform, modifying and non-modifying
    template <typename UnaryOperation>
    AudioScriptBuffer& apply(UnaryOperation op);
    template <typename UnaryOperation>
    AudioScriptBuffer applied(UnaryOperation op) const;
    template <typename BinaryOperation>
    AudioScriptBuffer& apply(const AudioScriptBuffer& other, BinaryOperation op);
    template <typename BinaryOperation>
    AudioScriptBuffer& applied(const AudioScriptBuffer& other, BinaryOperation op) const;

private:
    friend class AudioScriptEngine;
    // AudioScriptBuffer stores the memory of objects in a sort of "dead" state
    // after they are destroyed so that new buffers can reuse it. However, this
    // results in unreleased memory, so this function may be called to free it.
    // IMPORTANT: call this function when the buffer sizes used changes
    static void releaseMemory();
    // places buffer in deadBuffer if appropriate
    void bury();
    // attempts to retrieve a buffer from deadBuffer. Called only during construction
    bool resurrect();
    // actually deallocates the buffer
    void destroy();

    static size_t m_size;
    static int m_count;

    sample_t* m_data;
};

// template member function implementations
#include "audioscriptbuffer_p.h"

#endif // AUDIOSCRIPTBUFFER_H
