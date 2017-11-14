#include "audioscript.h"

#ifdef AS_ENABLE_REGISTER_METHODS

void AudioScript::registerDouble(std::function<double(AudioScript*)> getter,
                                 std::function<void(AudioScript*, double)> setter,
                                 const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(getter, setter), name);
}

void AudioScript::registerFloat(std::function<float(AudioScript*)> getter,
                                std::function<void(AudioScript*, float)> setter,
                                const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(getter, setter), name);
}
void AudioScript::registerBool(std::function<bool(AudioScript*)> getter,
                               std::function<void(AudioScript*, bool)> setter,
                               const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(getter, setter), name);
}
void AudioScript::registerInt(std::function<int(AudioScript*)> getter,
                              std::function<void(AudioScript*, int)> setter,
                              const std::string& name)
{
    getLibrary()->registerMember(AudioScriptVariant(getter, setter), name);
}

#endif
