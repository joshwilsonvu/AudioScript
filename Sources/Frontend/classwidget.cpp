#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QComboBox>
#include <QVariant>
#include <QAction>

#include "classwidget.h"
#include "dialogs.h"

ClassWidget::ClassWidget(QWidget* parent, Qt::WindowFlags flags)
    : SideWidgetBase(parent, flags), m_classes(new QListWidget()),
      m_groupBox(new QGroupBox(tr("Available classes"))),
      m_comboBox(new QComboBox()), m_classLoader(Q_NULLPTR)
{
    m_classes->setSelectionMode(QListWidget::SingleSelection);

    // Create layout with contents
    QVBoxLayout* layout = new QVBoxLayout();
    m_comboBox->addItem(QString());
    QAction* showDialog = new QAction("Select directory...", this);
    m_comboBox->addAction(showDialog);
    layout->addWidget(m_classes);

    // Add to titled GroupBox
    m_groupBox->setLayout(layout);

    connect(m_classes, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(onDoubleClicked(QListWidgetItem*)));
    connect(showDialog, SIGNAL(triggered(bool)),
            this, SLOT(onDirectorySelectorClicked()));
}

ClassWidget::~ClassWidget()
{
}

void ClassWidget::init(ClassLoader *classLoader)
{
    m_classLoader = classLoader;

}

void ClassWidget::onDoubleClicked(QListWidgetItem* item)
{
    emit doubleClicked(item->text());
}

void ClassWidget::onDirectorySelectorClicked() {
    DirDialog* d = new DirDialog(m_comboBox->itemText(0), this);
    if (d->exec() == DirDialog::Accepted && m_classLoader) {
        m_classLoader->setDirectory(d->selectedFiles().first());
        m_classes->clear();
        m_classes->addItems(m_classLoader->classes());
        m_comboBox->setCurrentIndex(0);
        m_comboBox->setCurrentText(m_classLoader->currentDirectory());
    }
}
