#ifndef AUDIOSCRIPTLIBRARY_H
#define AUDIOSCRIPTLIBRARY_H

#include <QPluginLoader>
#include <QString>
#include <memory>

class AudioScript;
class AudioScriptFactory;

// AudioScriptPlugin
// one-to-one plugin and AudioScript subclass
class AudioScriptPlugin {
public:
    AudioScriptPlugin(QString filename);
    AudioScriptPlugin(AudioScriptPlugin&& rhs);
    ~AudioScriptPlugin();

    QString name() const; // the name of the class subclassing AudioScript
    QString info() const; // information about the class subclassing AudioScript
    QString errorString() const; // the string reported if the library has an error

    bool spawnable() const;
    AudioScript* spawn();
    void unspawn(AudioScript* spawned);

private:
    QPluginLoader m_plugin;
    AudioScriptFactory* m_factory;
    int m_spawnedCount;
    const QString m_name; // retrieved from plugin once, guaranteed constant
    const QString m_info; // retrieved from plugin once, guaranteed constant
};


#endif // AUDIOSCRIPTLIBRARY_H
