#ifndef AUDIOSCRIPTLIBRARY_H
#define AUDIOSCRIPTLIBRARY_H

#include <memory>

#include <QPluginLoader>
#include <QString>
//#include <QMap>

#include "audioscript.h"
#include "audioscriptfactory.h"

class AudioScript;

// AudioScriptPlugin
// one-to-one library and AudioScript subclass
class AudioScriptPlugin {
public:
    AudioScriptPlugin(QString filename);
    AudioScriptPlugin(AudioScriptPlugin&& rhs);
    ~AudioScriptPlugin();

    QString name() const; // the name of the class subclassing AudioScript
    /*debug*/QString errorString() const; // the string reported if the library has an error

    bool spawnable() const;
    AudioScript* spawn();

private:
    QPluginLoader m_plugin;
    const QString m_name; // retrieved from plugin once, guaranteed constant
    AudioScriptFactory* m_factory;
};


#endif // AUDIOSCRIPTLIBRARY_H
