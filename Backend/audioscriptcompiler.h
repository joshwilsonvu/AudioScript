#ifndef AUDIOSCRIPTCOMPILER_H
#define AUDIOSCRIPTCOMPILER_H

#include <QString>
#include <QStringList>
#include <QObject>

class AudioScriptCompiler : public QObject
{
    Q_OBJECT

public:
    explicit AudioScriptCompiler(QObject* parent = Q_NULLPTR);
    ~AudioScriptCompiler() override;

    bool build(QString className);

    bool clean(QString className);

private:
    // pointer to corresponding
};

#endif // AUDIOSCRIPTCOMPILER_H
