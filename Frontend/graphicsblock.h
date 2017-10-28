#ifndef GRAPHICSBLOCK_H
#define GRAPHICSBLOCK_H

#include <QGraphicsItem>
#include <QSizeF>
#include <QRectF>

class GraphicsBlock : public QGraphicsItem
{
public:
    GraphicsBlock(QGraphicsItem* parent = 0, QString text = QString());
    virtual ~GraphicsBlock();

    virtual QRectF boundingRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget);

private:
    QPointF m_sz;
    QString m_text;
};

#endif // GRAPHICSBLOCK_H
