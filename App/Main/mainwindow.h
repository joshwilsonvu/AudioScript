#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scriptwindow.h"
#include "engine.h"
#include "blockarea.h"
#include "pluginmanager.h"

#include <QMainWindow>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openScriptWindow();
    void scriptWindowClosed();
    void onPluginFound(Plugin&);

    void start();
    void stop();

    void reset();

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
    QGraphicsView* m_graphicsView;

    Engine m_engine;
    PluginManager m_pluginManager;
};

#endif // MAINWINDOW_H
