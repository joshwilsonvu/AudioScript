#include <limits>
#include "sidewidgetbase.h"

SideWidgetBase::SideWidgetBase(QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
    setFixedWidth(300);
    setMinimumHeight(200);
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
