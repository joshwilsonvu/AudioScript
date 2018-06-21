#ifndef AS_PLUGIN_H
#define AS_PLUGIN_H

#include <QPluginLoader>
#include <QString>
#include <QStringList>

namespace AS {

class Script;
class Package;

// Plugin
// Represents a collection of Script types under a single package.
// Loaded from one plugin file.
class Plugin {
public:
    explicit Plugin(QString filename);
    Plugin(Plugin&& rhs);
    ~Plugin();

    // call with care, any active Scripts from this plugin will cause errors
    bool unload();

    QString errorString() const;

    QStringList getNames() const;

    QString getPackage() const;

    // if scriptName is empty, returns true if the Package is valid
    bool canGet(QString scriptName = "") const;

    Script* get(QString scriptName) const;

    QString getDescription(QString scriptName) const;


private:
    QPluginLoader m_plugin;
    Package* m_factory;
    QStringList m_names;
};

} // AS


#endif // AS_PLUGIN_H
