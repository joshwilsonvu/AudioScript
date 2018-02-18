#ifndef SCRIPTWINDOW_H
#define SCRIPTWINDOW_H

//#include <QMainWindow>
#include <QWidget>

#include "audioscriptcompiler.h"
#include "engine.h"
#include "plugin.h"
#include "classloader.h"

class ClassDialog;
class ApplicationOutput;
class AudioControls;
class CodeTabs;
class QHBoxLayout;

namespace Ui {
class ScriptWindow;
}

// See documentation.txt for details
class ScriptWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptWindow(QWidget *parent = 0);
    virtual ~ScriptWindow();

    // return non-owning pointers to UI elements
    ApplicationOutput* applicationOutput() const;
    AudioControls* audioControls() const;

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private slots:
    // The only reason MainWindow is delegating these
    // functions is because they are connected to UI actions;
    void newClass();
    void openClass();
    bool closeClass();
    bool saveClass();
    void setDirectory();
    void about();

    void build();
    void clean();

    // Other slots
    void onDocumentModified();
    void onClassNameChanged(QString className);

private:
    void setupUi();
    void setupConnections();
    void initActions();

    void readSettings();
    void writeSettings();

    // Frontend pointers
    Ui::ScriptWindow* m_ui;
    CodeTabs* m_editor;
    ApplicationOutput* m_appOutput;

    // Backend
    ClassLoader* m_classLoader;

    QSet<Plugin>* m_libraries;
    Engine* m_engine;
    AudioScriptCompiler* m_compiler;
};

#endif // SCRIPTWINDOW_H
