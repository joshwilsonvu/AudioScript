namespace AS {

// implementations of Buffer template member functions
template <typename UnaryOperation>
Buffer& Buffer::apply(UnaryOperation op)
{
    std::transform(begin(), end(), begin(), op);
    return *this;
}

template <typename UnaryOperation>
Buffer Buffer::applied(UnaryOperation op) const
{
    return clone().apply(op);
}

template <typename BinaryOperation>
Buffer& Buffer::apply(const Buffer& other, BinaryOperation op)
{
    std::transform(begin(), end(), other.begin(), begin(), op);
    return *this;
}

template <typename BinaryOperation>
Buffer Buffer::applied(const Buffer& other, BinaryOperation op) const
{
    return clone().apply(other, op);
}

} // AS
