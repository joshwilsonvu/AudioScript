#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtDebug>
#include <QRegularExpression>
#include <QString>

#include "dialogs.h"
#include "classloader.h"


NameDialog::NameDialog(ClassLoader* classLoader, QWidget* parent)
    : QDialog(parent), m_classLoader(classLoader)
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

QString NameDialog::getName() const
{
    return m_name;
}

// slot
void NameDialog::validate(QString className) {
    static const QRegularExpression regex("^[A-Z][a-zA-Z0-9]*$");
    m_okay->setEnabled(className != "AudioScript"
            && regex.match(className).hasMatch()
            && !m_classLoader->classes().contains(className));
    if (m_okay->isEnabled()) {
        m_name = className;
    }
}

DirDialog::DirDialog(QString directory, QWidget* parent)
    : QFileDialog(parent, "Set AudioScript directory",
                  directory)
{
    setFileMode(QFileDialog::Directory);
    setAcceptMode(QFileDialog::AcceptOpen);
    setOption(QFileDialog::ShowDirsOnly);
}

DirDialog::~DirDialog()
{
}
