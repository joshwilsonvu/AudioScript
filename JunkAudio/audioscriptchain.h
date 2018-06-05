#ifndef AUDIOSCRIPTCHAIN_H
#define AUDIOSCRIPTCHAIN_H

#include "audioscript.h"
#include <vector>

class AudioScriptBuffer;

class AudioScriptChain : public AudioScript
{
public:
    AudioScriptChain(AudioScript* script = 0);
    ~AudioScriptChain() override;
    AudioScriptChain& add(AudioScript* script);

    AudioScriptBuffer process(AudioScriptBuffer input) override;
    void reset() override;

private:
    std::vector<AudioScript*> m_audioScript;
};

#endif // AUDIOSCRIPTCHAIN_H
