#ifndef GRAPHICSBLOCK_H
#define GRAPHICSBLOCK_H

#include <QGraphicsItem>
#include <QPointF>
#include <QRectF>

class AudioScript;

class AudioBlock : public QGraphicsItem
{
public:
    AudioBlock(AudioScript* script, QGraphicsItem* parent = 0);
    AudioBlock(AudioScript* script, AudioBlock* prev, AudioBlock* next, QGraphicsItem* parent = 0);
    virtual ~AudioBlock();

    virtual QRectF boundingRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget);

    AudioScript* script() const;

    AudioBlock* next() const;

    AudioBlock* prev() const;

    // connects first and second so that
    // first->next() == second, second->prev() == first
    friend void link(AudioBlock* first, AudioBlock* second);


private:
    AudioScript* m_script;
    AudioBlock* m_next;
    AudioBlock* m_prev;


    QString m_text;
    QPointF m_sz;

    static const int k_spacing = 10;
};

// removes block from its chain but does not break the chain
void unlink(AudioBlock* block);
// removes block from its chain and leaves chain broken
void cut(AudioBlock* block);

#endif // GRAPHICSBLOCK_H
