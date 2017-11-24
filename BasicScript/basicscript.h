#ifndef BASICSCRIPT_H
#define BASICSCRIPT_H

#include "audioscript.h"

class BasicScript : public AudioScript
{
public:

    ~BasicScript() override;

    sample_t process(sample_t sample) override;

    void reset() override;
};

#endif // BASICSCRIPT_H
