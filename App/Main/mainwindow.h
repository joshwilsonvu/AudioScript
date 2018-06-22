#ifndef AS_MAINWINDOW_H
#define AS_MAINWINDOW_H

#include "scriptwindow.h"
#include "engine.h"
#include "blockarea.h"

#include <QMainWindow>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

namespace AS {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openScriptWindow();
    void scriptWindowClosed();

    void start();
    void stop();

    void reset();

    void openPlugin();

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private:
    // sets up editor and side windows
    void setupUi();

    // connects the menu bar actions to MainWindow slots
    void initActions();

    // connects internal components together
    void setupConnections();

    void readSettings();

    Ui::MainWindow *m_ui;
    ScriptWindow* m_scriptWindow;
    BlockArea* m_blockArea;
    QPlainTextEdit* m_logOutput;
    QGraphicsView* m_graphicsView;

    Engine m_engine;
};

} // AS

#endif // AS_MAINWINDOW_H
