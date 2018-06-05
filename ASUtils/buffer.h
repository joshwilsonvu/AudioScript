#ifndef AS_BUFFER_H
#define AS_BUFFER_H

#include "globals.h"

/*
 * @brief A container object for audio samples.
 *
 * Much like a std::vector, a Buffer object is a container
 * for a buffer of audio samples, build on a raw pointer and a size field.
 * It provides methods to perform arithmetic and arbitrary function calls
 * on its contents and is STL-compliant.
 */

namespace AS {

class ASUTILS_EXPORT Buffer
{
public:
    typedef sample_t value_type;

    // Constructors and destructor
    Buffer(size_t size = 0ul, bool zeroInitialize = true);
    Buffer(size_t size, sample_t* data); // takes ownership, no copy
    Buffer(const Buffer& other);
    Buffer(Buffer&& other);
    ~Buffer() noexcept;

    // copy/move assignment operator
    Buffer& operator=(const Buffer& other);
    Buffer& operator=(Buffer&& other);

    // explicit copy/move assignment methods, returns reference to *this
    Buffer& copyAssign(const Buffer& other);
    Buffer& moveAssign(Buffer& other);
    void swap(Buffer& other) noexcept;

    // convienience function to create a copy
    Buffer clone() const;

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
    // Buffer& operator*=(sample_t x);
    // Buffer& operator*=(const Buffer& other);
    // ...

    /// Accepts a Callable that takes one parameter of type sample_t and returns
    /// a value of type sample_t.
    /// Modifies the object in-place.
    template <typename UnaryOperation>
    Buffer& apply(UnaryOperation op);

    template <typename UnaryOperation>
    Buffer& operator|= (UnaryOperation op) {
        return this->apply(op);
    }

    /// Accepts a Callable that takes one parameter of type sample_t and returns
    /// a value of type sample_t.
    /// Returns a new object without modifying the current instance.
    template <typename UnaryOperation>
    Buffer applied(UnaryOperation op) const;

    template <typename UnaryOperation>
    Buffer operator| (UnaryOperation op) const {
        return this->applied(op);
    }

    /// Accepts a Callable that takes two parameters of type sample_t and returns
    /// a value of type sample_t.
    /// Modifies the object in-place.
    template <typename BinaryOperation>
    Buffer& apply(const Buffer& other, BinaryOperation op);

    /// Accepts a Callable that takes two parameters of type sample_t and returns
    /// a value of type sample_t.
    /// Returns a new object without modifying the current instance.
    template <typename BinaryOperation>
    Buffer applied(const Buffer& other, BinaryOperation op) const;

    class PairProxy {
    public:
        PairProxy(const Buffer& first, const Buffer& second);

        template <typename BinaryOperation>
        Buffer operator| (BinaryOperation op) const {
            return first.applied(second, op);
        }

    private:
        const Buffer& first;
        const Buffer& second;
    };

    PairProxy operator& (const Buffer& other);

private:
    size_t m_size;
    sample_t* m_data;


};

} // AS

// template member function implementations
#include "buffer.tpp"

#endif // AS_BUFFER_H
