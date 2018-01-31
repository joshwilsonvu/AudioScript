// implementations of AudioScriptBuffer template member functions
template <typename UnaryOperation>
AudioScriptBuffer& AudioScriptBuffer::apply(UnaryOperation op)
{
    std::transform(begin(), end(), begin(), op);
    return *this;
}

template <typename UnaryOperation>
AudioScriptBuffer AudioScriptBuffer::applied(UnaryOperation op) const
{
    return clone().apply(op);
}

template <typename BinaryOperation>
AudioScriptBuffer& AudioScriptBuffer::apply(const AudioScriptBuffer& other,
                                            BinaryOperation op)
{
    std::transform(begin(), end(), other.begin(), other.end(), begin(), op);
    return *this;
}

template <typename BinaryOperation>
AudioScriptBuffer& AudioScriptBuffer::applied(const AudioScriptBuffer& other,
                                              BinaryOperation op) const
{
    return clone().apply(other, op);
}
