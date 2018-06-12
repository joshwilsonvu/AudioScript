#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audioblock.h"

#include <QGraphicsScene>
#include <QGridLayout>
#include <QtDebug>
#include <QDir>

namespace AS {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_scriptWindow(nullptr),
    m_blockArea(new BlockArea(this))
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
        m_ui->actionOpenEditor->setEnabled(false);
    }
}

void MainWindow::scriptWindowClosed()
{
    m_scriptWindow = nullptr;
    m_ui->actionOpenEditor->setEnabled(true);
}

void MainWindow::start()
{
    m_ui->actionStart->setEnabled(false);
    m_ui->actionStop->setEnabled(true);
    m_engine.start();
}

void MainWindow::stop()
{
    m_ui->actionStart->setEnabled(true);
    m_ui->actionStop->setEnabled(false);
    m_engine.stop();
}

void MainWindow::reset()
{

}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if ((!m_scriptWindow || m_scriptWindow->close())/* && more*/) {
        event->accept();
        QApplication::instance()->quit();
    } else {
        event->ignore();
    }
}

void MainWindow::setupUi()
{
    m_graphicsView = new QGraphicsView(m_blockArea, this);
    m_graphicsView->setRenderHint(QPainter::Antialiasing);
    m_graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    m_graphicsView->setFocusPolicy(Qt::NoFocus);

    constexpr int spacing = 10;
    constexpr int margin_dim = 10;
    QMargins margins(margin_dim, margin_dim, margin_dim, margin_dim);

    QGridLayout* layout = new QGridLayout(m_ui->centralwidget);
    layout->setSpacing(spacing);
    layout->setContentsMargins(margins);
    layout->addWidget(m_graphicsView, 0, 0);
    layout->setColumnStretch(0, 1);
}

void MainWindow::initActions()
{
    m_ui->actionQuit->setShortcut(QKeySequence::Quit);
    connect(m_ui->actionQuit, SIGNAL(triggered(bool)),
            QApplication::instance(), SLOT(quit()));

    connect(m_ui->actionOpenEditor, SIGNAL(triggered(bool)),
            this, SLOT(openScriptWindow()));

    connect(m_ui->actionStart, SIGNAL(triggered(bool)),
            this, SLOT(start()));
    connect(m_ui->actionStop, SIGNAL(triggered(bool)),
            this, SLOT(stop()));
}

void MainWindow::setupConnections()
{

}

void MainWindow::readSettings()
{

}

} // AS
