#ifndef AUDIOBLOCK_H
#define AUDIOBLOCK_H

#include "audioscript.h"
#include "audioscriptplugin.h"

#include <QGraphicsItem>
#include <QPointF>
#include <QRectF>

class AudioScriptWrapper;

class AudioBlock : public QGraphicsItem
{
public:
    AudioBlock(AudioScriptPlugin& library, QGraphicsItem* parent = 0);
    AudioBlock(AudioScriptPlugin& library, AudioBlock* prev, AudioBlock* next, QGraphicsItem* parent = 0);
    virtual ~AudioBlock() override;

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;

    // wrappers around member instance methods
    sample_t process(sample_t sample);

    void reset();

    QString name() const;

    QString info() const;

    // utility methods
    const AudioScriptPlugin& library() const;

    AudioScript* script() const;

    AudioBlock* next() const;

    AudioBlock* prev() const;

    // connects first and second so that
    // first->next() == second, second->prev() == first
    friend void link(AudioBlock* first, AudioBlock* second);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

private:
    // owns AudioScript instance
    AudioScript* m_script;

    AudioScriptPlugin& m_plugin;
    AudioBlock* m_next;
    AudioBlock* m_prev;

    QPointF m_sz;

    static const int k_spacing = 10;
};

// removes block from its chain but does not break the chain
void unlink(AudioBlock* block);
// removes block from its chain and leaves chain broken
void cut(AudioBlock* block);

#endif // AUDIOBLOCK_H
