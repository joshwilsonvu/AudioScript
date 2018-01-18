#ifndef AUDIOSCRIPTCHAIN_H
#define AUDIOSCRIPTCHAIN_H

#include "audioscript.h"

#include <vector>

class AudioScriptChain : public AudioScript
{
public:
    AudioScriptChain(AudioScript* script = 0);
    ~AudioScriptChain() override;
    AudioScriptChain& add(AudioScript* script);



private:
    std::vector<AudioScript*> m_audioScript;
};

#endif // AUDIOSCRIPTCHAIN_H
