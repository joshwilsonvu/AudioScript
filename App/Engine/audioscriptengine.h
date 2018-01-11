#ifndef AUDIOSCRIPTENGINE_H
#define AUDIOSCRIPTENGINE_H

#include "audioscriptplugin.h"

#include <QObject>
#include <map>

class AudioScriptEngine : public QObject
{
    Q_OBJECT
public:
    explicit AudioScriptEngine(QObject *parent = nullptr);
    ~AudioScriptEngine();


signals:
    void pluginFound(AudioScriptPlugin&);

public slots:
    // make the engine aware of a new library
    // creates AudioScriptLibrary, adds to audioScriptLibraries, makes available
    //bool registerAudioScript(QString name);
    void findPlugins();

private:




    std::map<QString, AudioScriptPlugin> m_audioScriptPlugins;
};

#endif // AUDIOSCRIPTENGINE_H
