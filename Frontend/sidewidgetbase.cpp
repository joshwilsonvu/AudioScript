#include <limits>
#include "sidewidgetbase.h"

const QSize SideWidgetBase::m_size = QSize(300, 150);

SideWidgetBase::SideWidgetBase(QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
    setFixedWidth(m_size.width());
    setMinimumHeight(m_size.height());
    setMaximumHeight(QWidget::maximumHeight());
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
}

SideWidgetBase::~SideWidgetBase() {}

QSize SideWidgetBase::sizeHint() const
{
    return minimumSize();
}

QSize SideWidgetBase::minimumSizeHint() const
{
    return minimumSize();
}
