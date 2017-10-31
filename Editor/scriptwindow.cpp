#include <QtWidgets>
#include <QFile>
#include <QPlainTextEdit>
#include <QtDebug>
#include <QGridLayout>
#include <QSizePolicy>

#include "scriptwindow.h"
#include "ui_scriptwindow.h"
#include "dialogs.h"

// GUI interfaces on side areas
#include "classdialog.h"
#include "applicationoutput.h"
#include "audiocontrols.h"

ScriptWindow::ScriptWindow(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ScriptWindow()), m_editor(Q_NULLPTR), m_classLoader(Q_NULLPTR),
    m_libraries(Q_NULLPTR), m_engine(Q_NULLPTR), m_compiler(Q_NULLPTR)
{
    m_ui->setupUi(this); // sets up actions

    setupUi(); // sets up editor and output window

    setWindowIcon(QIcon(":/icons/application"));

    readSettings();

    initActions();

    m_editor->header()->setFocus();

    m_classLoader = new ClassLoader(m_editor, this); // requires editor valid
    onClassNameChanged(QString());

    setupConnections();
}

ScriptWindow::~ScriptWindow()
{
    delete m_ui;
    m_ui = Q_NULLPTR;
}

// Override
void ScriptWindow::closeEvent(QCloseEvent *event)
{
    if (m_classLoader->closeClass()) {
        writeSettings();
        event->accept();
        deleteLater();
    } else {
        event->ignore();
    }
}

void ScriptWindow::newClass()
{
    NameDialog* dialog = new NameDialog(m_classLoader, this);
    if (dialog->exec() == NameDialog::Accepted) {
        m_classLoader->newClass(dialog->getName());
    }
    dialog->deleteLater();
    // else, do nothing
}


void ScriptWindow::openClass()
{
    ClassDialog* dialog = new ClassDialog(m_classLoader, this);
    if (dialog->exec() == ClassDialog::Accepted) {
        m_classLoader->openClass(dialog->selectedClass());
    }
}

bool ScriptWindow::closeClass()
{
    if (m_classLoader->closeClass()) {
        m_appOutput->append(tr("Class closed."));
        return true;
    }
    return false;
}

bool ScriptWindow::saveClass()
{
    if (m_classLoader->saveClass()) {
        m_appOutput->append(tr("Class saved."));
        return true;
    } else {
        m_appOutput->append(tr("Unable to save class."));
        return false;
    }
}

void ScriptWindow::setDirectory()
{
    DirDialog* d = new DirDialog(m_classLoader->currentDirectory(), this);
    if (d->exec() == DirDialog::Accepted) {
        m_classLoader->setDirectory(d->selectedFiles().first());
        m_appOutput->append(m_classLoader->currentDirectory());
    }
}

void ScriptWindow::about()
{
    QFile aboutFile(":/docs/about");
    if (aboutFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::about(this, tr("About AudioScript"),
                           aboutFile.readAll());
    }
}

void ScriptWindow::build()
{
    m_compiler->build(m_classLoader->currentClass());
}

void ScriptWindow::clean()
{
    m_compiler->clean(m_classLoader->currentClass());
}



void ScriptWindow::onDocumentModified()
{
    setWindowModified(true);
}

void ScriptWindow::setupUi()
{
    constexpr int spacing = 6;
    constexpr int margin_dim = 10;
    QMargins margins(margin_dim, margin_dim, margin_dim, margin_dim);

    // Lay out left, right
    QGridLayout* layout = m_ui->gridLayout;
    layout->setSpacing(spacing);
    layout->setContentsMargins(margins);

    // Top
    m_editor = new CodeTabs();
    m_editor->setObjectName(QStringLiteral("editor"));
    m_editor->setEnabled(true);
    m_editor->setMinimumSize(QSize(300, 275));
    m_editor->setFocusPolicy(Qt::StrongFocus);
    m_editor->header()->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_editor->source()->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    layout->addWidget(m_editor, 0, 0);
    layout->setColumnStretch(0, 1);

    // Bottom
    m_appOutput = new ApplicationOutput(this);
    layout->addWidget(m_appOutput, 1, 0);
    layout->setColumnStretch(1, 0);

    setMinimumWidth(m_appOutput->minimumWidth() + m_editor->minimumWidth());
    setMinimumHeight(qMax(m_appOutput->minimumHeight(), m_editor->minimumHeight()));
}

void ScriptWindow::setupConnections() {
    // call documentWasModified when user changes contents of editor
    connect(m_editor->header()->document(), &QTextDocument::contentsChanged,
            this, &ScriptWindow::onDocumentModified);
    connect(m_editor->source()->document(), &QTextDocument::contentsChanged,
            this, &ScriptWindow::onDocumentModified);

    // connect the frontend graphics to the backend code
    connect(m_classLoader, SIGNAL(currentClassChanged(QString)), this, SLOT(onClassNameChanged(QString)));
}

void ScriptWindow::initActions() {
    m_ui->actionNew->setShortcut(QKeySequence::New);
    m_ui->actionNew->setStatusTip(tr("Create a new class"));
    connect(m_ui->actionNew, SIGNAL(triggered(bool)),
            this, SLOT(newClass()));

    m_ui->actionOpen->setShortcut(QKeySequence::Open);
    m_ui->actionOpen->setStatusTip(tr("Open an existing class"));
    connect(m_ui->actionOpen, SIGNAL(triggered(bool)),
            this, SLOT(openClass()));

    m_ui->actionSave->setShortcut(QKeySequence::Save);
    m_ui->actionSave->setStatusTip(tr("Save the open class"));
    connect(m_ui->actionSave, SIGNAL(triggered(bool)),
            this, SLOT(saveClass()));

    m_ui->actionClose->setShortcut(QKeySequence::Close);
    m_ui->actionClose->setStatusTip(tr("Close the open class"));
    connect(m_ui->actionClose, SIGNAL(triggered(bool)),
            this, SLOT(closeClass()));

    m_ui->actionSet_Directory->setStatusTip(tr("Set the AudioScript working directory"));
    connect(m_ui->actionSet_Directory, SIGNAL(triggered(bool)),
            this, SLOT(setDirectory()));

    m_ui->actionQuit->setShortcut(QKeySequence::Quit);
    connect(m_ui->actionQuit, SIGNAL(triggered(bool)),
            QApplication::instance(), SLOT(quit()));

    m_ui->actionAbout->setShortcut(QKeySequence::HelpContents);
    m_ui->actionAbout->setStatusTip(tr("About AudioScript"));
    connect(m_ui->actionAbout, SIGNAL(triggered(bool)),
            this, SLOT(about()));

    m_ui->actionAbout_Qt->setStatusTip(tr("Show the Qt library's about box"));
    connect(m_ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);

}

void ScriptWindow::readSettings()
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

void ScriptWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
}

void ScriptWindow::onClassNameChanged(QString className)
{
    setWindowModified(false);
    setWindowTitle(className);

    bool classOpen = !className.isEmpty();
    m_ui->actionClose->setEnabled(classOpen);
    m_ui->actionSave->setEnabled(classOpen);
}
