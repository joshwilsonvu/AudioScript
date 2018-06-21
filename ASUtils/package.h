#ifndef AS_FACTORY_H
#define AS_FACTORY_H

#include "script.h"
#include "globals.h"
#include <QtPlugin>
#include <map>
#include <string>
#include <vector>

#define AS_PACKAGE_IID "AudioScript.AS.Factory"

// macro to be included in private section of subclasses
#define AS_PACKAGE \
    Q_PLUGIN_METADATA(IID AS_PACKAGE_IID) \
    Q_INTERFACES(AS::Package)

namespace AS {

class ASUTILS_EXPORT Package
{
public:
    // The public interface of the Package class. Subclasses will not use these
    // methods.
    Package();

    virtual ~Package();

    /**
     * @brief getNames returns a list of all Script names this factory can spawn
     * @example return { "Filter.Biquad", "Compressor", "Distortion.Screamer" };
     */
    virtual const char* const* getNames() const final;

    /**
     * @brief getPackage returns the name of this package (collection) of Scripts
     *
     * A package is a unique identifier that groups all Scripts defined in getNames().
     *
     */
    virtual const char* getPackage() const final;

    /**
     * @brief canGet returns true if get(scriptName) will return a valid Script*
     */
    virtual bool canGet(const char* scriptName) const final;

    /**
     * @brief get returns a new instance of the Script specified by name
     * @param name one of the names given in getNames()
     */
    virtual Script* get(const char* scriptName) const final;

    /**
     * @brief getDescription describes the Script specified by name
     * @param name one of the names given in getNames()
     */
    virtual const char* getDescription(const char* scriptName) const final;

protected:
    // The protected interface of the Package class. Subclasses will use these
    // methods in their contructors to set up the package.
    struct ScriptProperties {
        ScriptProperties();

        const char* description;
        Script* (*spawner) ();
    };

    virtual void package(const char* packageName) final;
    virtual ScriptProperties& script(const char* scriptName) final;

    template <typename T>
    static Script* spawn();

private:
    const ScriptProperties* getProperties(const char* scriptName) const;

    std::map<std::string, ScriptProperties> m_scripts;
    std::vector<const char*> m_names;
    const char* m_package;
};

template<typename T>
Script* Package::spawn()
{
    static_assert(std::is_base_of<Script, T>::value, "Not a subclass of AS::Script.");
    return new T;
}

} // AS

// tells meta-object system about interface
Q_DECLARE_INTERFACE(AS::Package, AS_PACKAGE_IID)

#endif // AUDIOSCRIPTFACTORY_H
