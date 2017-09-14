#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "audioscriptcompiler.h"
#include "audioscriptengine.h"
#include "audioscriptlibrary.h"
#include "classloader.h"

class ClassWidget;
class ApplicationOutput;
class AudioScriptChain;
class AudioControls;
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
    ClassWidget* classWidget() const;
    ApplicationOutput* applicationOutput() const;
    AudioScriptChain* audioScriptChain() const;
    AudioControls* audioControls() const;

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private slots:
    // Connected to menu actions
    void newClass();
    void openClass(const QString& className);
    bool closeClass();
    bool saveClass();
    void about();

    void build(const QString& className);
    void clean(const QString& className);
    void rebuild(const QString& className);

    // Other slots
    void onDocumentModified();
    void onClassNameChanged(const QString& className);

private:
    void setupUi();
    void setupConnections();
    void initActions();
    void createStatusBar();

    void readSettings();
    void writeSettings();

    // Frontend pointers
    Ui::MainWindow* m_ui;
    CodeTabs* m_editor;
    ClassWidget* m_classWidget;
    ApplicationOutput* m_appOutput;
    AudioScriptChain* m_chain;
    AudioControls* m_audioControls;

    // Backend
    ClassLoader* m_classLoader;

    QSet<AudioScriptLibrary>* m_libraries;
    AudioScriptEngine* m_engine;
    AudioScriptCompiler* m_compiler;
};

#endif // MAINWINDOW_H
