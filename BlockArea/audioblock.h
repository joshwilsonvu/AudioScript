#ifndef GRAPHICSBLOCK_H
#define GRAPHICSBLOCK_H

#include <QGraphicsItem>
#include <QPointF>
#include <QRectF>

class AudioScriptWrapper;

class AudioBlock : public QGraphicsItem
{
public:
    typedef typename AudioScript::sample_t sample_t;

    AudioBlock(AudioScript* script, AudioScriptLibrary* library, QGraphicsItem* parent = 0);
    AudioBlock(AudioScriptWrapper* script, AudioScriptLibrary* library, AudioBlock* prev, AudioBlock* next, QGraphicsItem* parent = 0);
    virtual ~AudioBlock() override;

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;

    sample_t process(sample_t);

    void reset();

    QString name() const;

    AudioScriptWrapper* script() const;

    AudioBlock* next() const;

    AudioBlock* prev() const;

    // connects first and second so that
    // first->next() == second, second->prev() == first
    friend void link(AudioBlock* first, AudioBlock* second);


private:
    AudioScript* m_script;
    AudioScriptLibrary* m_library;
    AudioBlock* m_next;
    AudioBlock* m_prev;

    QPointF m_sz;

    static const int k_spacing = 10;
};

// removes block from its chain but does not break the chain
void unlink(AudioBlock* block);
// removes block from its chain and leaves chain broken
void cut(AudioBlock* block);

#endif // GRAPHICSBLOCK_H
