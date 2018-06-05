#ifndef AS_EXCEPTION_H
#define AS_EXCEPTION_H

namespace AS {

class Exception
{
public:
    Exception(const char* what = "");
    const char* what() const;
private:
    const char* m_what;
};

} // AS

#endif // AS_EXCEPTION_H
