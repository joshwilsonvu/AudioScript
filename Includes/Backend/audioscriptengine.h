#ifndef AUDIOSCRIPTENGINE_H
#define AUDIOSCRIPTENGINE_H

#include <QObject>
#include <QString>
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
    bool registerAudioScript(const QString& name);

    void changeDirectory(const QString& directory);

private:
    QMap<QString, AudioScriptLibrary*> m_audioScriptLibraries;
    QList<AudioScript*> m_activeAudioScripts;
};

#endif // AUDIOSCRIPTENGINE_H
