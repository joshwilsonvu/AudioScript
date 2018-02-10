#ifndef AUDIOSCRIPTBUFFER_H
#define AUDIOSCRIPTBUFFER_H

#include "globals.h"

class ASUTILS_EXPORT AudioScriptBuffer
{
public:
    typedef sample_t value_type;

    // Constructors and destructor
    AudioScriptBuffer(size_t size = 0ul, bool zeroInitialize = true);
    AudioScriptBuffer(const AudioScriptBuffer& other);
    AudioScriptBuffer(AudioScriptBuffer&& other);
    ~AudioScriptBuffer() noexcept;

    // copy/move assignment operator
    AudioScriptBuffer& operator=(const AudioScriptBuffer& other);
    AudioScriptBuffer& operator=(AudioScriptBuffer&& other);

    // explicit copy/move assignment methods, returns reference to *this
    AudioScriptBuffer& copyAssign(const AudioScriptBuffer& other);
    AudioScriptBuffer& moveAssign(AudioScriptBuffer& other);
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
    size_t m_size;
    sample_t* m_data;
};

// template member function implementations
#include "audioscriptbuffer_p.h"

#endif // AUDIOSCRIPTBUFFER_H
