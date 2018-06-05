#include "exception.h"

namespace AS {

Exception::Exception(const char* what)
    : m_what(what)
{
}

const char* Exception::what() const
{
    return m_what;
}

} // AS
