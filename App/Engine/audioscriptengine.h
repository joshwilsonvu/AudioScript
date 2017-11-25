#ifndef AUDIOSCRIPTENGINE_H
#define AUDIOSCRIPTENGINE_H

#include <QObject>
#include <map>
#include <QList>

#include "audioscriptplugin.h"

class AudioScriptEngine : public QObject
{
    Q_OBJECT
public:
    explicit AudioScriptEngine(QObject *parent = Q_NULLPTR);
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
