#ifndef AUDIOSCRIPTBUFFER_H
#define AUDIOSCRIPTBUFFER_H

#include "globals.h"
#include "audioformat.h"
#include <vector>

class ASUTILS_EXPORT AudioScriptBuffer
{
public:
    typedef sample_t value_type;

    AudioScriptBuffer(AS::BufferSize bufferSize);
    AudioScriptBuffer(const AudioFormat& format);

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

    // AudioScriptBuffer stores the memory of objects in a sort of "dead" state
    // after they are destroyed so that new buffers can reuse it. However, this
    // results in memory unreleased memory, so this function may be called to
    // free it.
    static void releaseMemory();
private:
    // places buffer in deadBuffer if appropriate
    static void bury(AudioScriptBuffer&& buffer);
    // attempts to retrieve a buffer from deadBuffer, size zero if failed
    static AudioScriptBuffer resurrect(AS::BufferSize bufferSize);
    // generates a buffer with no resources
    AudioScriptBuffer();
    // actually deallocates the buffer
    void destroy();

    const static size_t DEADBUFFER_CAPACITY = 10;
    static std::vector<AudioScriptBuffer> deadBuffer;

    size_t m_size;
    sample_t* m_data;
};

// template member function implementations
#include "audioscriptbuffer_p.h"

#endif // AUDIOSCRIPTBUFFER_H
