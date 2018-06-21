#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audioblock.h"
#include "log.h"

#include <QBuffer>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QtDebug>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>

namespace AS {

// helper free function
QString persistentDataDirectory() {
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_scriptWindow(nullptr),
    m_blockArea(new BlockArea(this)),
    m_logDevice(new QBuffer(this)),
    m_logOutput(new QTextEdit(this))
{
    m_logDevice->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
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

void MainWindow::openPlugin()
{
    QString dir = persistentDataDirectory();
    QString file = QFileDialog::getOpenFileName(this, tr("Open Plugin"),
                                                    dir,
                                                    tr("Plugins (*.so *.dylib *.dll)"));
    AS::log() << "Loading:" << file;
    QString pluginName = m_engine.load(file);
    if (pluginName.isEmpty()) {
        AS::log() << "Not a plugin";
    } else {
        AS::log() << "Package" << pluginName << "loaded.";
    }
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

    m_logOutput->setReadOnly(true);
    m_logOutput->setAcceptRichText(false);

    constexpr int spacing = 10;
    constexpr int margin_dim = 10;
    QMargins margins(margin_dim, margin_dim, margin_dim, margin_dim);

    QGridLayout* layout = new QGridLayout(m_ui->centralwidget);
    layout->setSpacing(spacing);
    layout->setContentsMargins(margins);
    layout->addWidget(m_graphicsView, 0, 0);
    layout->setColumnStretch(0, 1);
    layout->addWidget(m_logOutput, 1, 0);
    layout->setColumnStretch(1, 0);
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

    connect(m_ui->actionOpenPlugin, SIGNAL(triggered(bool)),
            this, SLOT(openPlugin()));
}

void MainWindow::setupConnections()
{
    // set the global log destination to m_logDevice, and write to m_logOutput
    AS::setLogDestination(m_logDevice);
    connect(m_logDevice, &QIODevice::readyRead, [this] () {
        auto str = QString(m_logDevice->buffer());
        m_logDevice->buffer().clear();
        m_logOutput->append(str);
    });
}

void MainWindow::readSettings()
{

}

} // AS
