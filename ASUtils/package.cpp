#include "package.h"

namespace AS {

// Factory
Package::Package()
    :  m_names(1, nullptr), m_package("DefaultPackage")
{}

Package::~Package() {}

const char* const* Package::getNames() const
{
    return &m_names[0];
}

const char* Package::getPackage() const
{
    return m_package;
}

bool Package::canGet(const char* scriptName) const
{
    auto properties = getProperties(scriptName);
    return properties && properties->spawner;
}

Script* Package::get(const char* scriptName) const
{
    auto properties = getProperties(scriptName);
    if (properties && properties->spawner) {
        return properties->spawner();
    }
    return nullptr;
}

const char* Package::getDescription(const char* scriptName) const
{
    auto properties = getProperties(scriptName);
    if (properties) {
        return properties->description ? : "Default description.";
    }
    return nullptr;
}

void Package::package(const char* packageName)
{
    m_package = packageName ? : "DefaultPackage";
}

Package::ScriptProperties& Package::script(const char* scriptName)
{
    // keep m_names up to date with m_scripts, so that it can return all keys
    if (!m_scripts.count(scriptName)) {
        // add a new name, keeping the list sorted and null-terminated
        auto iter = std::upper_bound(m_names.begin(), m_names.end() - 1, scriptName,
                                     [] (const char* a, const char* b) {
            return std::strcmp(a, b) < 0;
        });
        m_names.insert(iter, scriptName);
    }
    // create an entry in m_scripts if necessary, and return a reference to
    // the (new) ScriptProperties instance
    return m_scripts[scriptName];
}

const Package::ScriptProperties* Package::getProperties(const char* scriptName) const
{
    auto iter = m_scripts.find(scriptName);
    if (iter != m_scripts.end()) {
        auto& properties = iter->second;
        return &properties;
    }
    return nullptr;
}

// Factory::ScriptProperties
Package::ScriptProperties::ScriptProperties()
    : description("Default description."),
      spawner(nullptr)
{}

} // AS
