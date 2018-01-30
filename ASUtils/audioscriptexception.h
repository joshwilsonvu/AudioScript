#ifndef AUDIOSCRIPTEXCEPTION_H
#define AUDIOSCRIPTEXCEPTION_H

class AudioScriptException
{
public:
    AudioScriptException(const char* what);
    const char* what() const;
private:
    const char* m_what;
};

#endif // AUDIOSCRIPTEXCEPTION_H
