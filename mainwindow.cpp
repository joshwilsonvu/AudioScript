#include <QtWidgets>
#include <QFile>
#include <QPlainTextEdit>
#include <QtDebug>
#include <QHBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "language.h"
#include "dialogs.h"

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

    editor()->header()->setLineWrapMode(QPlainTextEdit::NoWrap);
    editor()->source()->setLineWrapMode(QPlainTextEdit::NoWrap);
    editor()->header()->setFocus();

    // call documentWasModified when user changes contents of editor
    connect(editor()->header()->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentWasModified);
    connect(editor()->source()->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentWasModified);

    m_classLoader = new ClassLoader(this); // requires setupUi() complete

}

MainWindow::~MainWindow()
{
    delete m_ui;
    m_ui = nullptr;
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
    if (dialog->exec() == NameDialog::Accepted &&
            m_classLoader->newClass(className)) {
        setCurrentClass(className);
    }
    dialog->deleteLater();
    // else, do nothing
}

/*
void MainWindow::openClass()
{
    QString className("DEFAULT"); // debug
    ClassDialog* dialog = new ClassDialog(className, this, ClassDialog::Open); // owned by this
    if (dialog->exec() == ClassDialog::Accepted && maybeSave()) {
        loadClass(className);
        setCurrentClass(className);
    }
    dialog->deleteLater();
}
*/

bool MainWindow::closeClass()
{
    if (m_classLoader->closeClass()) {
        setCurrentClass(QString());
        statusBar()->showMessage(tr("Class closed"), 5000);
        return true;
    }
    return false;
}

bool MainWindow::saveClass()
{
    if (m_classLoader->saveClass()) {
        setCurrentClass(m_classLoader->currentClass());
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

void MainWindow::documentWasModified()
{
    setWindowModified(true);
}

void MainWindow::setupUi()
{
    QHBoxLayout* horizontalLayout = new QHBoxLayout(m_ui->centralWidget);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);

    m_editor = new CodeTabs();
    m_editor->setObjectName(QStringLiteral("editor"));
    m_editor->setEnabled(true);
    m_editor->setMinimumSize(QSize(300, 150));
    m_editor->setFocusPolicy(Qt::StrongFocus);
    horizontalLayout->addWidget(m_editor);
    // reparents editor to centralWidget


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

void MainWindow::setCurrentClass(const QString &className)
{
    setWindowModified(false);
    setWindowTitle(className);
}
