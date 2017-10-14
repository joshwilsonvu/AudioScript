#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_scriptWindow(Q_NULLPTR)
{
    m_ui->setupUi(this); // sets up menu bar, status bar, actions

    setupUi();

    setWindowIcon(QIcon(":/icons/application"));

    readSettings();

    initActions();

    setupConnections();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::openScriptWindow()
{
    if (!m_scriptWindow) {
        m_scriptWindow = new ScriptWindow();
        connect(m_scriptWindow, SIGNAL(destroyed(QObject*)),
                this, SLOT(scriptWindowClosed()));
        m_scriptWindow->show();
        m_scriptWindow->raise();
        m_ui->actionOpen_Editor->setEnabled(false);
    }
}

void MainWindow::scriptWindowClosed()
{
    m_scriptWindow = Q_NULLPTR;
    m_ui->actionOpen_Editor->setEnabled(true);
}

void MainWindow::play()
{

}

void MainWindow::stop()
{

}

void MainWindow::reset()
{

}

void MainWindow::setupUi()
{

}

void MainWindow::initActions()
{
    m_ui->actionQuit->setShortcut(QKeySequence::Quit);
    connect(m_ui->actionQuit, SIGNAL(triggered(bool)),
            QApplication::instance(), SLOT(quit()));

    connect(m_ui->actionOpen_Editor, SIGNAL(triggered(bool)),
            this, SLOT(openScriptWindow()));
}

void MainWindow::setupConnections()
{

}

void MainWindow::readSettings()
{

}
