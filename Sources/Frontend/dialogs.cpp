#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtDebug>
#include <QRegularExpression>

#include "dialogs.h"

#include <QString>

NameDialog::NameDialog(QString* value, QWidget* parent)
    : QDialog(parent), m_value(value)
{
    setSizeGripEnabled(true);
    setModal(true); // use exec() not show()

    QHBoxLayout* layout(new QHBoxLayout(this));
    m_label = new QLabel(tr("New class name:"), this);
    layout->addWidget(m_label);

    m_classInput = new QLineEdit(this);
    m_label->setBuddy(m_classInput);
    connect(m_classInput, SIGNAL(textChanged(QString)),
            this, SLOT(validate(QString)));
    layout->addWidget(m_classInput);

    m_okay = new QPushButton(tr("Done"), this);
    m_okay->setDefault(true);
    m_okay->setEnabled(false);
    connect(m_okay, SIGNAL(clicked(bool)),
            this, SLOT(accept()));
    layout->addWidget(m_okay);
    setLayout(layout);
}

// slot
void NameDialog::validate(const QString& className) {
    static const QRegularExpression regex("^[A-Z][a-zA-Z0-9]*$");
    m_okay->setEnabled(className != "AudioScript"
            && regex.match(className).hasMatch());
    if (m_okay->isEnabled()) {
        *m_value = className;
    }
}

DirDialog::DirDialog(const QString& directory, QWidget* parent)
    : QFileDialog(parent, "Select a directory for your AudioScripts",
                  directory)
{
    setFileMode(QFileDialog::Directory);
    setAcceptMode(QFileDialog::AcceptSave);
    setOption(QFileDialog::ShowDirsOnly);
}
