#include "graphicsblock.h"

#include <QPainter>
#include <QPointF>
#include <QStyleOptionGraphicsItem>

GraphicsBlock::GraphicsBlock(QGraphicsItem* parent, QString text)
    : QGraphicsItem(parent), m_sz(100, 80), m_text(text)
{

}

GraphicsBlock::~GraphicsBlock()
{

}

QRectF GraphicsBlock::boundingRect() const
{
    return QRectF(-0.5f * m_sz, 0.5f * m_sz);
}

void GraphicsBlock::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rect = boundingRect();
    qreal pw = 1.0f;
    // shrink drawing area for pen width
    rect.adjust(0.5f*pw,0.5f*pw, -0.5f*pw, -0.5f*pw);
    painter->setBrush(Qt::lightGray);
    painter->setPen(QPen(Qt::black, pw));
    painter->drawRoundedRect(rect, rect.width()/5, rect.height()/5);
    painter->drawText(rect, m_text, QTextOption(Qt::AlignCenter));
}
