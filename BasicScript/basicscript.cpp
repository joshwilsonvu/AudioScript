#include "basicscript.h"
typedef typename BasicScript::sample_t sample_t;

BasicScript::~BasicScript() {}

sample_t BasicScript::process(sample_t sample)
{
    return sample * 0.5f;
}

void BasicScript::reset() {}
