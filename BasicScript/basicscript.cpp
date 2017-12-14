#include "basicscript.h"

BasicScript::~BasicScript()
{

}

sample_t BasicScript::process(sample_t sample)
{
    return sample * 0.5f;
}

void BasicScript::reset()
{

}
