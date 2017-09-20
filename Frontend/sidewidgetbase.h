#ifndef SIDEWIDGETBASE_H
#define SIDEWIDGETBASE_H

#include <QWidget>

class SideWidgetBase : public QWidget
{
public:
    SideWidgetBase(QWidget* parent = Q_NULLPTR, Qt::WindowFlags flags = 0);

    virtual ~SideWidgetBase();

    virtual QSize sizeHint() const override;

    virtual QSize minimumSizeHint() const override;

private:
    static const QSize m_size;
};

#endif // SIDEWIDGETBASE_H
