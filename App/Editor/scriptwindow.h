#ifndef AS_SCRIPTWINDOW_H
#define AS_SCRIPTWINDOW_H

//#include <QMainWindow>
#include <QWidget>

#include "classloader.h"

class ClassDialog;
class ApplicationOutput;
class AudioControls;
class CodeTabs;
class QHBoxLayout;

namespace Ui {
class ScriptWindow;
}

namespace AS {

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
};

} // AS

#endif // AS_CRIPTWINDOW_H
