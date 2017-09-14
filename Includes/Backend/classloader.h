#ifndef CLASSLOADER_H
#define CLASSLOADER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QStringList>

#include "codetabs.h"

class MainWindow;
class ClassWidget;

class ClassLoader : public QObject
{
    Q_OBJECT

public:
    ClassLoader(MainWindow* parent);
    virtual ~ClassLoader();

    void init(ClassWidget* classWidget);

    // The monitored directory containing all files used
    QString currentDirectory() const;
    // The class that is currently open in the editor, or empty string
    QString currentClass() const;
    // The list of classes in the directory, may or may not be spawnable
    QStringList classes() const;

    // Class is not open in editor
    bool newClass(const QString& className); // name dialog
    bool openClass(const QString& className); // fail dialog?
    //void deleteClass(const QString& className);
    // Class is open in editor
    bool closeClass();
    bool saveClass();

    bool setDirectory(const QString& dirName);

signals:
    // connect with AudioScriptCompiler so that it may automatically compile
    void classUpdated(QString); // or added
    void classRemoved(QString); // remove library
    void directoryChanged(ClassLoader*);

private:
    bool maybeSave();
    void readSettings();

    static QString loadFromFile(const QString& fileName);
    static bool saveToFile(const QString& text, const QString& fileName);

    // null if no class open, contains name of open class otherwise
    QString m_className;
    // all classes in the selected directory
    QStringList m_classes;
    // empty if no directory selected, contains path otherwise. Saved
    QString m_directory;
    // non-owning pointers to MainWindow GUIS
    CodeTabs* m_editor;
    ClassWidget* m_classWidget;
    // child QObject monitoring directory
    QFileSystemWatcher* m_fileSystem;
};

#endif // CLASSLOADER_H
