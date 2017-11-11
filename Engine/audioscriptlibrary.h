#ifndef AUDIOSCRIPTLIBRARY_H
#define AUDIOSCRIPTLIBRARY_H

#include <string>
#include <memory>

#include <QPluginLoader>
#include <QString>
#include <QMap>

#include "audioscriptvariant.h"
#include "audioscriptfactory.h"

class AudioScript;

// AudioScriptLibrary contains
// immutable, one-to-one library and AudioScript subclass
class AudioScriptLibrary {
public:
    AudioScriptLibrary(QPluginLoader&& plugin);
    ~AudioScriptLibrary();

    QString name() const; // the name of the class subclassing AudioScript
    /*debug*/QString errorString() const; // the string reported if the library has an error

    bool spawnable() const;
    std::unique_ptr<AudioScript> spawn();

    //void registerMember(AudioScriptVariant&& member, const std::string& name);

private:
    typedef AudioScript* (*SpawnFunction)(void);

    QString m_name;
    QPluginLoader m_plugin;
    AudioScriptFactory* m_factory;

    //QMap<QString, AudioScriptVariant> m_members;
};


#endif // AUDIOSCRIPTLIBRARY_H
