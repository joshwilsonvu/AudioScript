#ifndef AUDIOSCRIPTLIBRARY_H
#define AUDIOSCRIPTLIBRARY_H

#include <QLibrary>
#include <QString>
#include <QVector>

#include "audioscriptvariant.h"

class AudioScript;

// AudioScriptLibrary contains
// immutable, one-to-one library and AudioScript subclass
class AudioScriptLibrary {
public:
    AudioScriptLibrary(const QString& name);
    ~AudioScriptLibrary();

    QString name() const; // the name of the class subclassing AudioScript
    QString errorString() const; // the string reported if the library has an error

    bool spawnable() const;
    AudioScript* spawn(); // dynamically allocated

    // need name of member, pointer to member, type of member
    void registerMember(AudioScriptVariant&& member);

private:
    typedef AudioScript* (*SpawnFunction)(void);

    QString m_name;
    QLibrary m_library;
    SpawnFunction m_spawnFunction;

    QVector<MemberVariant> m_members;
};


#endif // AUDIOSCRIPTLIBRARY_H
