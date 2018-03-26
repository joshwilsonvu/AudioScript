#ifndef PLUGIN_H
#define PLUGIN_H

#include <QPluginLoader>
#include <QString>
#include <memory>

class AudioScript;
class AudioScriptFactory;

// Plugin
// one-to-one plugin and AudioScript subclass
class Plugin {
public:
    Plugin(QString filename);
    Plugin(Plugin&& rhs);
    ~Plugin();

    bool unload();

    QString name() const; // the name of the class subclassing AudioScript
    QString info() const; // information about the class subclassing AudioScript
    QString errorString() const; // the string reported if the library has an error

    bool spawnable() const;
    AudioScript* spawn();


private:
    QPluginLoader m_plugin;
    AudioScriptFactory* m_factory;
    const QString m_name; // retrieved from plugin once, guaranteed constant
    const QString m_info; // retrieved from plugin once, guaranteed constant
};


#endif // PLUGIN_H
