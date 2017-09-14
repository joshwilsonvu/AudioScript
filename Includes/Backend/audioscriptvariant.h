#ifndef AUDIOSCRIPTVARIANT_H
#define AUDIOSCRIPTVARIANT_H

#include <string>
#include <QString>

class AudioScript;

// Marshals registered parameters, enabling GUI interfaces to change values
// in real time.
class AudioScriptVariant
{
public:
    AudioScriptVariant();
    AudioScriptVariant(double AudioScript::* p_member, const std::string& name);
    AudioScriptVariant(float AudioScript::* p_member, const std::string& name);
    AudioScriptVariant(int AudioScript::* p_member, const std::string& name);
    AudioScriptVariant(bool AudioScript::* p_member, const std::string& name);

    enum MemberType {
        Double,
        Float,
        Int,
        Bool,
        None
    };
    MemberType type() const;
    QString name() const;

    // Return Q_NULLPTR if type() does not match
    double* toDouble(AudioScript* audioScript);
    float* toFloat(AudioScript* audioScript);
    int* toInt(AudioScript* audioScript);
    bool* toBool(AudioScript* audioScript);

private:
    MemberType m_type;

    unsigned char AudioScript::* m_ptrToMember;

    QString m_name;
};

#endif // AUDIOSCRIPTVARIANT_H
