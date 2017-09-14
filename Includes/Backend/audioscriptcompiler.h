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
/*
public slots:
    bool build(const QString& className);
    bool buildAll(const QStringList& classes);

    bool clean(const QString& className);
    bool cleanAll(const QStringList& classes);

    bool rebuild(const QString& className); // clean && build
    bool rebuildAll(const QStringList& classes);

private:

*/
};

#endif // AUDIOSCRIPTCOMPILER_H
