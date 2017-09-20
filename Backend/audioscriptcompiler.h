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
    bool buildAll(const QStringList& classes);

    bool clean(QString className);
    bool cleanAll(const QStringList& classes);

    bool rebuild(QString className); // clean && build
    bool rebuildAll(const QStringList& classes);

private:

};

#endif // AUDIOSCRIPTCOMPILER_H
