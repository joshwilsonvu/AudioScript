#ifndef AUDIOSCRIPTGUI_H
#define AUDIOSCRIPTGUI_H

#include "globals.h"
#include "audioscript.h"
#include <functional>

class QWidget;

class ASUTILS_EXPORT AudioScriptUI
{

public:
    explicit AudioScriptUI();

    typedef std::function<double(const AudioScript*)> DoubleGetter;
    typedef std::function<void(AudioScript*, double)> DoubleSetter;
    typedef std::function<float(const AudioScript*)> FloatGetter;
    typedef std::function<void(AudioScript*, float)> FloatSetter;
    typedef std::function<bool(const AudioScript*)> BoolGetter;
    typedef std::function<void(AudioScript*, bool)> BoolSetter;
    typedef std::function<int(const AudioScript*)> IntGetter;
    typedef std::function<void(AudioScript*, int)> IntSetter;


    void addProperty(DoubleGetter getter, DoubleSetter setter, std::string name);
    void addProperty(FloatGetter getter, FloatSetter setter, std::string name);
    void addProperty(BoolGetter getter, BoolSetter setter, std::string name);
    void addProperty(IntGetter getter, IntSetter setter, std::string name);
    //void addProperty();


    void show(AudioScript* script);

};

#endif // AUDIOSCRIPTGUI_H
