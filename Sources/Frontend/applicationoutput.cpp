#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFontMetrics>

#include "applicationoutput.h"

ApplicationOutput::ApplicationOutput(QWidget* parent, Qt::WindowFlags flags)
    : SideWidgetBase(parent, flags),
      m_display(new QPlainTextEdit(tr("Application output will be displayed here.\n"))),
      m_groupBox(new QGroupBox(tr("Application output"), this))
{
    // Create layout with contents
    QVBoxLayout* layout = new QVBoxLayout(this);
    m_display->setReadOnly(true);
    m_display->setAutoFillBackground(false);
    m_display->setMaximumBlockCount(128);
    m_display->setCenterOnScroll(true);
    m_display->setMinimumHeight(m_display->fontMetrics().height() * 8);
    layout->addWidget(m_display, 1);

    // Add to titled GroupBox
    m_groupBox->setLayout(layout);
}

ApplicationOutput::~ApplicationOutput()
{
}

void ApplicationOutput::append(const QString& text)
{
    m_display->appendPlainText(text);
}
