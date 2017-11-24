#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QtDebug>

#include "classdialog.h"
#include "dialogs.h"

ClassDialog::ClassDialog(ClassLoader* classLoader, QWidget* parent, Qt::WindowFlags flags)
    : QDialog(parent, flags), m_classes(new QListWidget()),
      m_groupBox(new QGroupBox(tr("Available classes")))
{
    m_classes->setSelectionMode(QListWidget::SingleSelection);
    m_classes->addItems(classLoader->classes());
    m_classes->setCurrentRow(0);

    // Create layout with contents
    QVBoxLayout* groupLayout = new QVBoxLayout(this);
    groupLayout->addWidget(m_classes, 1);

    // Add to titled GroupBox
    m_groupBox->setLayout(groupLayout);

    // Lay out GroupBox
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_groupBox);

    connect(m_classes, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(onDoubleClicked(QListWidgetItem*)));
}

ClassDialog::~ClassDialog()
{
}

void ClassDialog::onDoubleClicked(QListWidgetItem* item)
{
    m_selectedClass = item->text();
    accept();
}

QString ClassDialog::selectedClass() const
{
    return m_selectedClass;
}

/*
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
*/
