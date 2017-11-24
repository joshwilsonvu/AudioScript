#ifndef AUDIOSCRIPTLIBRARY_H
#define AUDIOSCRIPTLIBRARY_H

#include <memory>

#include <QPluginLoader>
#include <QString>
//#include <QMap>

#include "audioscript.h"
#include "audioscriptfactory.h"

class AudioScript;

// AudioScriptLibrary contains
// immutable, one-to-one library and AudioScript subclass
class AudioScriptLibrary {
public:
    AudioScriptLibrary(QString filename);
    ~AudioScriptLibrary();

    QString name() const; // the name of the class subclassing AudioScript
    /*debug*/QString errorString() const; // the string reported if the library has an error

    bool spawnable() const;
    AudioScript* spawn();

    //void registerMember(AudioScriptVariant&& member, const std::string& name);

private:
    QPluginLoader m_plugin;
    const QString m_name; // retrieved from plugin once, guaranteed constant
    AudioScriptFactory* m_factory;

    //QMap<QString, AudioScriptVariant> m_members;
};


#endif // AUDIOSCRIPTLIBRARY_H
