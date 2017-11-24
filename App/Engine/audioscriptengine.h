#ifndef AUDIOSCRIPTENGINE_H
#define AUDIOSCRIPTENGINE_H

#include <QObject>
#include <QMap>
#include <QList>

#include "audioscriptlibrary.h"

class AudioScriptEngine : public QObject
{
    Q_OBJECT
public:
    explicit AudioScriptEngine(QObject *parent = Q_NULLPTR);
    ~AudioScriptEngine();


signals:

public slots:
    // make the engine aware of a new library
    // creates AudioScriptLibrary, adds to audioScriptLibraries, makes available
    //bool registerAudioScript(QString name);

private:
    QMap<QString, AudioScriptLibrary*> m_audioScriptLibraries;
    QList<AudioScript*> m_activeAudioScripts;
};

#endif // AUDIOSCRIPTENGINE_H
