#ifndef CLASSLOADER_H
#define CLASSLOADER_H

#include <QObject>
#include <QStringList>

#include "codetabs.h"

// change ClassLoader to FilesLoader, on slot load(QStringList filenames)
// emit signal loaded(QStringList files)
// load files atomically -- true if all succeed, false and no change otherwise
// slot save(QStringList filenames, QStringList files);
// emit signal saved(QStringList files)

class QFileSystemWatcher;

class ClassLoader : public QObject
{
    Q_OBJECT

public:
    ClassLoader(CodeTabs* editor, QObject* parent = nullptr);
    virtual ~ClassLoader();

    // The monitored directory containing all files used
    QString currentDirectory() const;
    // The class that is currently open in the editor, or empty string
    QString currentClass() const;
    // The list of classes in the directory, may or may not be spawnable
    QStringList classes() const;

    // Class is not open in editor
    bool newClass(QString className); // name dialog
    bool openClass(QString className); // fail dialog?

    // Class is open in editor
    bool closeClass();
    bool saveClass();

    bool setDirectory(QString dirName);

signals:
    // connect with AudioScriptCompiler so that it may automatically compile
    void currentClassChanged(QString);
    void classSaved(QString);
    void directoryChanged(ClassLoader*);

private:
    bool maybeSave();

    static QString loadFromFile(QString fileName);
    static bool saveToFile(QString text, QString fileName);

    // null if no class open, contains name of open class otherwise
    QString m_className;
    // all classes in the selected directory
    QStringList m_classes;
    // empty if no directory selected, contains path otherwise. Saved
    QString m_directory;
    // non-owning pointers to MainWindow GUIS
    CodeTabs* m_editor;
    // child QObject monitoring directory
    QFileSystemWatcher* m_fileSystem;
};

#endif // CLASSLOADER_H
