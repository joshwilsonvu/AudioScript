
#include "../compiler.h"

#include <string>

bool Compiler::build(const char* className)
{
    return std::string(className).empty();
}

bool Compiler::clean(const char* className)
{
    return std::string(className).empty();
}
