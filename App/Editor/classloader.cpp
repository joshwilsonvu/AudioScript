#include "classloader.h"
#include "scriptwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QStringList>
#include <QtDebug>
#include <QFile>
#include <QSaveFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QSettings>
#include <QFileSystemWatcher>




// Public
// Precondition: parent->editor() must be valid
ClassLoader::ClassLoader(CodeTabs* editor, QObject* parent)
    : QObject(parent), m_editor(editor),
      m_fileSystem(new QFileSystemWatcher(this))
{
    closeClass();

    QSettings settings;
    QString directory = settings.value("directory", QString()).toString();
    // set path in if statement if directory not empty, check if ddirectory exists
    if (!directory.isEmpty() && QDir(directory).exists()) {
        setDirectory(directory);
    }
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
bool ClassLoader::newClass(QString className)
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
    emit currentClassChanged(m_className);
    return true;

}

bool ClassLoader::openClass(QString className)
{
    if (!maybeSave()) {
        return false;
    }
    QString headerText = loadFromFile(m_directory + QDir::separator() + className + ".hpp");
    QString sourceText = loadFromFile(m_directory + QDir::separator() + className + ".cpp");
    if (headerText.isEmpty() || sourceText.isEmpty()) {
        qDebug() << "Failed to open AudioScript class.";
        return false;
    }
    m_editor->setPlainText(headerText, sourceText);
    m_editor->setReadOnly(false);
    m_className = className;
    emit currentClassChanged(m_className);
    return true;
}

/*
void ClassLoader::deleteClass(QString className)
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
    emit currentClassChanged(m_className);
    return true;
}

bool ClassLoader::saveClass()
{
    if (m_className.isEmpty()) {
        return true; // do nothing if no class open, still "successful"
    }
    bool headerModified = m_editor->header()->document()->isModified();
    bool sourceModified = m_editor->source()->document()->isModified();

    bool good = saveToFile(m_editor->header()->toPlainText(),
                           currentDirectory() + QDir::separator() + m_className + ".hpp")
            &&  saveToFile(m_editor->source()->toPlainText(),
                           currentDirectory() + QDir::separator() + m_className + ".cpp");
    m_editor->header()->document()->setModified(!good && headerModified);
    m_editor->source()->document()->setModified(!good && sourceModified);
    if (good && (headerModified || sourceModified)) {
            emit classSaved(m_className);
    }
    return good;
}

bool ClassLoader::setDirectory(QString dirName)
{
    // TODO: Currently, don't check whether we are changing to the same directory;
    // makes initialization easier
    QDir class_directory(dirName);
    if (!class_directory.exists()) {
        return false;
    }

    QStringList removables = m_fileSystem->files() + m_fileSystem->directories();
    if (!removables.empty()) {
        m_fileSystem->removePaths(m_fileSystem->files() + m_fileSystem->directories());
    }
    m_classes.clear();

    {
        QSettings settings;
        settings.setValue("directory", dirName);
    }
    m_directory = dirName;
    m_fileSystem->addPath(m_directory);

    // clear class list and fill with files, watch for changes
    class_directory.setFilter(QDir::Files | QDir::Readable | QDir::Writable);
    class_directory.setSorting(QDir::Name);
    QStringList sources = class_directory.entryList(QStringList()
                                                    << "*.cpp" << "*.cxx" << "*.cc");
    QStringList headers = class_directory.entryList(QStringList()
                                                    << "*.hpp" << "*.hxx" << "*.hh" << "*.h");

    // only do the following if there are hpp or cpp files
    if (sources.size() > 0 && headers.size() > 0) {
        for(QString& source : sources) {
            source.resize(source.lastIndexOf('.')); // remove extension
        }
        for(QString& header : headers) {
            header.resize(header.lastIndexOf('.')); // remove extension
        }

        QStringList::iterator s = sources.begin();
        QStringList::iterator h = headers.end();

        while (s != sources.end() && h != headers.end()) {
            int cmp = QString::localeAwareCompare(*s, *h);
            if (cmp == 0) {
                // strings match, add class
                if (!m_classes.contains(*s)) {
                    m_classes << *s; // add class
                    ++s;
                    ++h;
                } else {
                    qDebug() << "Handle duplicate class name!!";
                }
            } else if (cmp < 0) {
                // s is behind h (ex., no header file); skip
                ++s;
            } else {
                // h is behind s (ex., no source file); skip
                ++h;
            }
        }
    }

    emit directoryChanged(this);
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
            = QMessageBox::warning(qobject_cast<QWidget*>(parent()), tr("AudioScript"),
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

// static
QString ClassLoader::loadFromFile(QString fileName)
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
bool ClassLoader::saveToFile(QString text, QString fileName)
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
