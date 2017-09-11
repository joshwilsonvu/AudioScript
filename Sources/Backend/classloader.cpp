#include "classloader.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QtDebug>
#include <QFile>
#include <QSaveFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QSettings>

// Public
// Precondition: parent->editor() must be valid
ClassLoader::ClassLoader(MainWindow* parent)
    : QObject(parent), m_editor(parent->editor()),
      m_fileSystem(new QFileSystemWatcher(this))
{
    closeClass();

    readSettings();
}

ClassLoader::~ClassLoader()
{
    // class has already been closed (and maybe saved)
    m_editor = Q_NULLPTR; // non-owning
}

QString ClassLoader::currentDirectory() const
{
    return m_directory;
}

QString ClassLoader::currentClass() const
{
    return m_className;
}

QStringList ClassLoader::classes() const
{
    return m_classes;
}

// Class is not open in editor
bool ClassLoader::newClass(const QString &className)
{
    if (!maybeSave()) {
        return false;
    }
    QString headerText = loadFromFile(":/defaults/header");
    QString sourceText = loadFromFile(":/defaults/source");
    if (headerText.isEmpty() || sourceText.isEmpty()) {
        return false; // do nothing, defaults should be non-empty
    }
    headerText.replace("CLASSNAME", className); // no tr()
    sourceText.replace("CLASSNAME", className); // no tr()

    m_editor->setPlainText(headerText, sourceText);
    m_editor->setReadOnly(false);
    m_className = className;
    return true;

}

bool ClassLoader::openClass(const QString& className)
{
    if (!maybeSave()) {
        return false;
    }
    QString headerText = loadFromFile(m_directory + className + ".hpp");
    QString sourceText = loadFromFile(m_directory + className + ".cpp");
    if (headerText.isEmpty() || sourceText.isEmpty()) {
        qDebug() << "Failed to open default AudioScript file.";
        return false;
    }
    m_editor->setPlainText(headerText, sourceText);
    m_editor->setReadOnly(false);
    m_className = className;
    return true;
}

/*
void ClassLoader::deleteClass(const QString& className)
{
    if (className == m_className) {
        // TODO display "Can't delete open class" message
        return;
    } else {
        QFile file(className + ".hpp");
        if (file.exists()) {
            file.remove();
        }
        file.setFileName(className + ".cpp");
        if (file.exists()) {
            file.remove();
        }
    }
    // TODO sketchy because library file could exist and
    // be inside the AudioScriptLibrary map
}
*/

// Class is open in editor
bool ClassLoader::closeClass()
{
    if (!maybeSave()) {
        return false;
    }
    m_editor->setReadOnly(true);
    QString introText = loadFromFile(":/defaults/intro");
    m_editor->setPlainText(introText, introText);
    m_className.clear(); // signify no class open
    return true;
}

bool ClassLoader::saveClass()
{
    if (m_className.isEmpty()) {
        return true; // do nothing if no class open, still "successful"
    }
    bool headerModified = m_editor->header()->document()->isModified();
    bool sourceModified = m_editor->source()->document()->isModified();

    // assume good if not modified, only save if not modified
    bool good = (!headerModified ||
                 saveToFile(m_editor->header()->toPlainText(), m_directory + m_className + ".hpp")) &&
            (!sourceModified ||
             saveToFile(m_editor->source()->toPlainText(), m_directory + m_className + ".cpp"));
    m_editor->header()->document()->setModified(!good && headerModified);
    m_editor->source()->document()->setModified(!good && sourceModified);
    return good;
}

bool ClassLoader::setDirectory(const QString &dirName)
{
    // TODO
    if (m_directory == dirName) {
        return true; // no change, "success"
    }
    m_fileSystem->removePath(m_directory);
    m_directory = dirName;
    // clear class list and fill with files, watch for changes
    return true;
}

// private
bool ClassLoader::maybeSave()
{
    if (m_className.isEmpty()) { // no class open, okay to scrap contents
        return true;
    }
    if (!m_editor->header()->document()->isModified() &&
            !m_editor->source()->document()->isModified())
        return true;
    const QMessageBox::StandardButton ret
            = QMessageBox::warning(qobject_cast<MainWindow*>(parent()), tr("Application"),
                                   tr("The class has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return saveClass();
    case QMessageBox::Cancel:
        return false;
    default:
        return true;
    }
}

void ClassLoader::readSettings()
{
    QSettings settings;
    m_directory = settings.value("directory", QString()).toString();
    QDir directory;

    // set path in if statement if m_directory not empty, check if directory exists
    if (m_directory.isEmpty() || (directory.setPath(m_directory), !directory.exists())) {
        return;
    }

    directory.setFilter(QDir::Files | QDir::Readable | QDir::Writable);
    QStringList filters;
    filters << "*.hpp" << "*.cpp";
    directory.setNameFilters(filters);
    directory.setSorting(QDir::Name);

    QStringList files = directory.entryList(); // sorted,
    qDebug() << files;
    m_classes.clear();
    for (QStringList::iterator i = files.begin(); i != files.end(); ++i) {
        if (i->endsWith(".cpp") && (i+1) != files.end() && (i+1)->endsWith(".hpp")) {
            QString source = *i;
            QString header = *(++i);
            source.remove(".cpp");
            header.remove(".hpp");
            if (source == header) { // both hold class name alone
                m_classes << source;
            }
        }
    }
}

// static
QString ClassLoader::loadFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot open file " << fileName;
        return QString(); // failed
    }

#ifndef QT_NO_CURSOR
    // indicates process that may take time
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    QString text = file.readAll();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    return text;
}

// static
bool ClassLoader::saveToFile(const QString& text, const QString& fileName)
{
    QSaveFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Cannot open file " << fileName;
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    // indicates process that may take time
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << text;
    bool committed = file.commit();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    return committed;
}


/*
void NameDialog::refreshAvailableClasses() {
    m_availableClasses.clear();
    QSettings settings;
    QDir class_directory(settings.value("class_directory", QString()).toString());
    {
        class_directory.setFilter(QDir::Files | QDir::Readable | QDir::Writable);
        QStringList filters;
        filters << "*.hpp" << "*.cpp";
        class_directory.setNameFilters(filters);
        class_directory.setSorting(QDir::Name);
    }
    QStringList files = class_directory.entryList();
    m_availableClasses.clear();
    for (QStringList::iterator i = files.begin(); i != files.end(); ++i) {
        if (i->endsWith(".cpp") && (i+1) != files.end() && (i+1)->endsWith(".hpp")) {
            QString source = *i;
            QString header = *(++i);
            source.remove(".cpp");
            header.remove(".hpp");
            if (source == header) { // both hold class name alone
                m_availableClasses << source;
            }
        }
    }
}
*/
