#include <QtWidgets>
#include <QFile>
#include <QPlainTextEdit>
#include <QtDebug>
#include <QGridLayout>
#include <QSizePolicy>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs.h"

// GUI interfaces on side areas
#include "classwidget.h"
#include "applicationoutput.h"
#include "audioscriptchain.h"
#include "audiocontrols.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow), m_editor(Q_NULLPTR), m_classLoader(Q_NULLPTR),
    m_libraries(Q_NULLPTR), m_engine(Q_NULLPTR), m_compiler(Q_NULLPTR)
{
    m_ui->setupUi(this); // sets up menu bar, status bar, actions

    setupUi(); // sets up editor and side windows

    setWindowIcon(QIcon(":/icons/application"));

    readSettings();

    initActions();
    createStatusBar();

    editor()->header()->setFocus();

    m_classLoader = new ClassLoader(this); // requires editor valid
    onClassNameChanged(QString());

    setupConnections();
}

MainWindow::~MainWindow()
{
    delete m_ui;
    m_ui = Q_NULLPTR;
}

CodeTabs* MainWindow::editor() const
{
    return m_editor;
}

// Override
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_classLoader->closeClass()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newClass()
{
    QString className("DEFAULT"); // debug
    NameDialog* dialog = new NameDialog(&className, this);
    if (dialog->exec() == NameDialog::Accepted) {
        m_classLoader->newClass(className);
    }
    dialog->deleteLater();
    // else, do nothing
}


void MainWindow::openClass(const QString& className)
{
    m_classLoader->openClass(className);
}

bool MainWindow::closeClass()
{
    if (m_classLoader->closeClass()) {
        statusBar()->showMessage(tr("Class closed"), 5000);
        return true;
    }
    return false;
}

bool MainWindow::saveClass()
{
    if (m_classLoader->saveClass()) {
        statusBar()->showMessage(tr("Class saved"), 5000);
        return true;
    } else {
        statusBar()->showMessage(tr("Unable to save class"), 5000);
        return false;
    }
}

void MainWindow::about()
{
    QFile aboutFile(":/docs/about");
    if (aboutFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::about(this, tr("About AudioScript"),
                           aboutFile.readAll());
    }
}

void MainWindow::onDocumentModified()
{
    setWindowModified(true);
}

void MainWindow::build(const QString& className)
{

}

void MainWindow::clean(const QString& className)
{

}

void MainWindow::rebuild(const QString& className)
{

}

void MainWindow::setupUi()
{
    constexpr int spacing = 0;
    constexpr int margin_dim = 10;
    QMargins margins(margin_dim, margin_dim, margin_dim, margin_dim);
    QSize minSize(QApplication::fontMetrics().averageCharWidth() * 25,
                  QApplication::fontMetrics().height() * 10);

    m_ui->centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Lay out left, center, right
    QGridLayout* layout = qobject_cast<QGridLayout*>(m_ui->centralWidget->layout());
    layout->setSpacing(spacing);
    layout->setContentsMargins(margins);

    // Left side
    m_classWidget = new ClassWidget();
    layout->addWidget(m_classWidget, 0, 0);

    m_appOutput = new ApplicationOutput();
    layout->addWidget(m_appOutput, 1, 0);

    // Center
    m_editor = new CodeTabs();
    m_editor->setObjectName(QStringLiteral("editor"));
    m_editor->setEnabled(true);
    m_editor->setMinimumSize(QSize(300, 275));
    m_editor->setFocusPolicy(Qt::StrongFocus);
    m_editor->header()->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_editor->source()->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    layout->addWidget(m_editor, 0, 1, -1, 1);

    // Right side
    m_chain = new AudioScriptChain();
    layout->addWidget(m_chain, 0, 2);

    m_audioControls = new AudioControls();
    layout->addWidget(m_audioControls, 1, 2);

    setMinimumWidth(qMax(m_classWidget->minimumWidth(), m_appOutput->minimumWidth())
                   + m_editor->minimumWidth()
                   + qMax(m_chain->minimumWidth(), m_audioControls->minimumWidth()));
    setMinimumHeight(qMax(m_classWidget->minimumHeight() + m_appOutput->minimumHeight(),
                        qMax(m_editor->minimumHeight(),
                             m_chain->minimumHeight() + m_audioControls->minimumHeight())));
}

void MainWindow::setupConnections() {
    // call documentWasModified when user changes contents of editor
    connect(editor()->header()->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::onDocumentModified);
    connect(editor()->source()->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::onDocumentModified);

    // connect the frontend graphics to the backend code
    connect(m_classWidget, SIGNAL(doubleClicked(QString)), this, SLOT(openClass(QString)));
    connect(m_classLoader, SIGNAL(classUpdated(QString)), this, SLOT(onClassNameChanged(QString)));
    connect(m_classLoader, SIGNAL(directoryChanged(ClassLoader*)),
            m_classWidget, SLOT(onDirectoryChanged(ClassLoader*)));
}

void MainWindow::initActions() {
    m_ui->actionNew->setShortcut(QKeySequence::New);
    m_ui->actionNew->setStatusTip(tr("Create a new class"));
    connect(m_ui->actionNew, SIGNAL(triggered(bool)),
            this, SLOT(newClass()));

    /*
    m_ui->actionOpen->setShortcut(QKeySequence::Open);
    m_ui->actionOpen->setStatusTip(tr("Open an existing class"));
    connect(m_ui->actionOpen, SIGNAL(triggered(bool)),
            this, SLOT(openClass());
    */

    m_ui->actionSave->setShortcut(QKeySequence::Save);
    m_ui->actionSave->setStatusTip(tr("Save the open class"));
    connect(m_ui->actionSave, SIGNAL(triggered(bool)),
            this, SLOT(saveClass()));

    m_ui->actionClose->setShortcut(QKeySequence::Close);
    m_ui->actionClose->setStatusTip(tr("Close the open class"));
    connect(m_ui->actionClose, SIGNAL(triggered(bool)),
            this, SLOT(closeClass()));

    m_ui->actionQuit->setShortcut(QKeySequence::Quit);
    connect(m_ui->actionQuit, SIGNAL(triggered(bool)),
            this, SLOT(close()));

    m_ui->actionAbout->setShortcut(QKeySequence::HelpContents);
    m_ui->actionAbout->setStatusTip(tr("About AudioScript"));
    connect(m_ui->actionAbout, SIGNAL(triggered(bool)),
            this, SLOT(about()));

    m_ui->actionAbout_Qt->setStatusTip(tr("Show the Qt library's about box"));
    connect(m_ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);

}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"), 5000);
}

void MainWindow::readSettings()
{
    QSettings settings;
    const QByteArray geometry = settings.value("geometry").toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
}

void MainWindow::onClassNameChanged(const QString &className)
{
    setWindowModified(false);
    setWindowTitle(className);

    bool classOpen = !className.isEmpty();
    m_ui->actionClose->setEnabled(classOpen);
    m_ui->actionSave->setEnabled(classOpen);
}
