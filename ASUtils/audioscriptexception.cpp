#include "audioscriptexception.h"

AudioScriptException::AudioScriptException(const char* what)
    : m_what(what)
{

}

const char* AudioScriptException::what() const
{
    return m_what;
}
