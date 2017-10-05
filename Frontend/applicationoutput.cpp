#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFontMetrics>

#include "applicationoutput.h"

ApplicationOutput::ApplicationOutput(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags),
      m_display(new QPlainTextEdit(tr("Application output will be displayed here.\n")))
{
    // Create layout with contents
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_display->setReadOnly(true);
    m_display->setAutoFillBackground(false);
    m_display->setMaximumBlockCount(1024);
    m_display->setCenterOnScroll(true);
    m_display->setFixedHeight(m_display->fontMetrics().height() * 8);
    m_display->setMaximumWidth(QWidget::maximumWidth());
    m_display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addWidget(m_display, 1);
}

ApplicationOutput::~ApplicationOutput()
{
}

void ApplicationOutput::append(QString text)
{
    m_display->appendPlainText(text);
}
