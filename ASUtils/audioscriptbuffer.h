#ifndef AUDIOSCRIPTBUFFER_H
#define AUDIOSCRIPTBUFFER_H

#include "globals.h"

class ASUTILS_EXPORT AudioScriptBuffer
{
public:
    typedef sample_t value_type;

    AudioScriptBuffer(size_t size);
    AudioScriptBuffer(const AudioScriptBuffer& other);
    AudioScriptBuffer(AudioScriptBuffer&& other);
    ~AudioScriptBuffer() noexcept;
    AudioScriptBuffer& operator=(AudioScriptBuffer other) noexcept;

    void swap(AudioScriptBuffer& other) noexcept;

    AudioScriptBuffer clone() const;

    void clear();
    void fill(sample_t value);

    // TODO maybe inline
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
