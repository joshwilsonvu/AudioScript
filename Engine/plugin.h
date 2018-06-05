#ifndef AS_PLUGIN_H
#define AS_PLUGIN_H

#include <QPluginLoader>
#include <QString>
#include <memory>

namespace AS {

class Script;
class Factory;

// Plugin
// one-to-one plugin and Script subclass
class Plugin {
public:
    Plugin(QString filename);
    Plugin(Plugin&& rhs);
    ~Plugin();

    bool unload();

    QString name() const; ///<the name of the class subclassing Script
    QString info() const; ///<information about the class subclassing Script
    QString errorString() const; ///<the string reported if the library has an error

    bool spawnable() const;
    Script* spawn();


private:
    QPluginLoader m_plugin;
    Factory* m_factory;
    QString m_name; // retrieved from plugin once, guaranteed constant
    QString m_info; // retrieved from plugin once, guaranteed constant
};

} // AS


#endif // AS_PLUGIN_H
