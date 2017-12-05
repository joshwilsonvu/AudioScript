#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audioblock.h"

#include <QGraphicsScene>
#include <QGridLayout>
#include <QtDebug>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_scriptWindow(Q_NULLPTR),
    m_graphicsScene(new QGraphicsScene(0,0,1,1,this)),
    m_engine(new AudioScriptEngine(this))
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

void MainWindow::onPluginFound(AudioScriptPlugin& plugin)
{
    m_graphicsScene->addItem(new AudioBlock(plugin));
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

    m_graphicsScene->setBackgroundBrush(Qt::white);

    m_graphicsView = new QGraphicsView(m_graphicsScene, this);
    m_graphicsView->setRenderHint(QPainter::Antialiasing);
    m_graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    m_graphicsView->setFocusPolicy(Qt::NoFocus);

    constexpr int spacing = 10;
    constexpr int margin_dim = 30;
    QMargins margins(margin_dim, margin_dim, margin_dim, margin_dim);

    QGridLayout* layout = new QGridLayout(m_ui->centralwidget);

    layout->setSpacing(spacing);
    layout->setContentsMargins(margins);

    layout->addWidget(m_graphicsView, 0, 0);
    layout->setColumnStretch(0, 1);

    // debug code
    //AudioScriptPlugin* lib = new AudioScriptPlugin(QString("../../../../BasicScript/libBasicScript.dylib"));
    //m_graphicsScene->addItem(new AudioBlock(*lib, Q_NULLPTR)); // TODO fix memory leak
}

void MainWindow::initActions()
{
    m_ui->actionQuit->setShortcut(QKeySequence::Quit);
    connect(m_ui->actionQuit, SIGNAL(triggered(bool)),
            QApplication::instance(), SLOT(quit()));

    connect(m_ui->actionOpen_Editor, SIGNAL(triggered(bool)),
            this, SLOT(openScriptWindow()));

    connect(m_ui->actionOpenPlugin, SIGNAL(triggered(bool)),
            m_engine, SLOT(findPlugins()));
}

void MainWindow::setupConnections()
{
    connect(m_engine, SIGNAL(pluginFound(AudioScriptPlugin&)), this, SLOT(onPluginFound(AudioScriptPlugin&)));
}

void MainWindow::readSettings()
{

}
