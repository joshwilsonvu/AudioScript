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
      m_comboBox(new QComboBox())
{
    // Create layout with contents
    QVBoxLayout* layout = new QVBoxLayout();
    m_comboBox->addItem(QString());
    QAction* showDialog = new QAction("Select directory...", this);
    connect(showDialog, SIGNAL(triggered(bool)), [&] () {
        DirDialog* d = new DirDialog(m_comboBox->itemText(0), this);
        d->exec();
        })
    m_comboBox->addAction(showDialog);
    layout->addWidget(m_classes);

    // Add to titled GroupBox
    m_groupBox->setLayout(layout);

    connect(m_classes, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(onDoubleClicked(QListWidgetItem*)));
}

ClassWidget::~ClassWidget()
{
}

void ClassWidget::onDirectoryChanged(ClassLoader* classLoader)
{
    m_comboBox->setItemText(0, classLoader->currentClass());
}

void ClassWidget::onDoubleClicked(QListWidgetItem* item)
{
    emit doubleClicked(item->text());
}

