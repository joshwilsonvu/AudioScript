#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "audioscriptcompiler.h"
#include "audioscriptengine.h"
#include "audioscriptlibrary.h"
#include "classloader.h"

class CodeTabs;
class QHBoxLayout;

namespace Ui {
class MainWindow;
}

// See documentation.txt for details
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    // return non-owning pointers to UI elements
    CodeTabs* editor() const;

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private slots:
    void newClass();
    //void openClass();
    bool closeClass();
    bool saveClass();
    void about();
    void documentWasModified();

private:
    void setupUi();
    void initActions();
    void createStatusBar();

    void readSettings();
    void writeSettings();
    void setCurrentClass(const QString& className);

    Ui::MainWindow* m_ui;
    CodeTabs* m_editor;

    ClassLoader* m_classLoader;

    QSet<AudioScriptLibrary>* m_libraries;
    AudioScriptEngine* m_engine;
    AudioScriptCompiler* m_compiler;
};

#endif // MAINWINDOW_H
