#ifndef COMPILER_H
#define COMPILER_H

class Compiler
{
public:
    bool build(const char* className);

    bool clean(const char* className);
};

#endif // COMPILER_H
