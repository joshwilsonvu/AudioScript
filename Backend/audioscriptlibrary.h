#ifndef AUDIOSCRIPTLIBRARY_H
#define AUDIOSCRIPTLIBRARY_H

#include <string>

#include <QLibrary>
#include <QString>
#include <QMap>

#include "audioscriptvariant.h"

class AudioScript;

// AudioScriptLibrary contains
// immutable, one-to-one library and AudioScript subclass
class AudioScriptLibrary {
public:
    AudioScriptLibrary(QString name);
    ~AudioScriptLibrary();

    QString name() const; // the name of the class subclassing AudioScript
    QString errorString() const; // the string reported if the library has an error

    bool spawnable() const;
    AudioScript* spawn(); // dynamically allocated

    void registerMember(AudioScriptVariant&& member, const std::string& name);

private:
    typedef AudioScript* (*SpawnFunction)(void);

    QString m_name;
    QLibrary m_library;
    SpawnFunction m_spawnFunction;

    QMap<QString, AudioScriptVariant> m_members;
};


#endif // AUDIOSCRIPTLIBRARY_H
