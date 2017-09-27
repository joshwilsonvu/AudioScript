#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "audioscriptcompiler.h"
#include "audioscriptengine.h"
#include "audioscriptlibrary.h"
#include "classloader.h"

class ClassDialog;
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
    ApplicationOutput* applicationOutput() const;
    AudioScriptChain* audioScriptChain() const;
    AudioControls* audioControls() const;

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private slots:
    // The only reason MainWindow is delegating these
    // functions is because they are connected to UI actions;
    // for inter-object communication, store pointers and provide link()
    void newClass();
    void openClass();
    bool closeClass();
    bool saveClass();
    void about();

    void build();
    void clean();

    void play();
    void stop();

    void clear();
    void enableAll();
    void disableAll();

    // Other slots
    void onDocumentModified();
    void onClassNameChanged(QString className);

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
    ApplicationOutput* m_appOutput;
    AudioScriptChain* m_chain;
    AudioControls* m_audioControls;

    // Backend
    ClassLoader* m_classLoader;

    QSet<AudioScriptLibrary>* m_libraries;
    AudioScriptEngine* m_engine;
    AudioScriptCompiler* m_compiler;
};

// the generic function
template <class T1, class T2>
void link(T1* t1, T2* t2) {
    t1->link(t2);
    t2->link(t1);
}

#endif // MAINWINDOW_H
