#ifndef AUDIOBLOCK_H
#define AUDIOBLOCK_H

#include "engine.h"

#include <QGraphicsItem>
#include <QPointF>
#include <QRectF>
#include <memory>

/**
 * In a previous iteration, the AudioBlock class owned an instance of a
 * Script subclass and a reference to a Plugin. However, these are implementation
 * details of the Engine class and do not coincide with the paradigm of using
 * only the public API of the module to be used.
 * In the future, AudioBlock will serve as an abstraction for the structure
 * that Engine supports, and changes to the AudioBlock structure will call
 * methods on Engine to make the corresponding change.
 */

namespace AS {

class Buffer;

class AudioBlock : public QGraphicsItem
{
public:
    AudioBlock(Engine* engine, QString plugin, QGraphicsItem* parent = 0);

    virtual ~AudioBlock() override;

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;

    QString name() const;

    // special block methods - things reserved for AudioScript App like
    // upsample, downsample, change Buffer data type, stereo->mono
    //bool isSpecial() const;
    //bool special(AudioSettings* settings, AS::Buffer* buffer);

    // utility methods
    AudioBlock* next() const;

    AudioBlock* prev() const;

    // connects first and second so that
    // first->next() == second, second->prev() == first
    static void link(AudioBlock* first, AudioBlock* second);
    // removes block from its chain but does not break the chain
    void unlink();
    // removes block from its chain and leaves chain broken
    void cut();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

private:
    Engine* m_engine;
    QString m_plugin;

    AudioBlock* m_next;
    AudioBlock* m_prev;

    QPointF m_sz;

    static const int k_spacing = 10;
};

} // AS

#endif // AUDIOBLOCK_H
