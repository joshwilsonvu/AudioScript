#ifndef AUDIOBLOCK_H
#define AUDIOBLOCK_H

#include "audioscript.h"
#include "plugin.h"

#include <QGraphicsItem>
#include <QPointF>
#include <QRectF>
#include <memory>

class AudioScriptBuffer;

class AudioBlock : public QGraphicsItem
{
public:
    AudioBlock(Plugin& plugin, QGraphicsItem* parent = 0);
    AudioBlock(Plugin& plugin, AudioBlock* prev, AudioBlock* next, QGraphicsItem* parent = 0);
    virtual ~AudioBlock() override;

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;

    // wrappers around member instance methods
    AudioScriptBuffer process(AudioScriptBuffer buffer);

    void reset();

    QString name() const;

    QString info() const;

    // special block methods - things reserved for AudioScript App like
    // upsample, downsample, change Buffer data type, stereo->mono
    //bool isSpecial() const;
    //bool special(AudioSettings* settings, AS::Buffer* buffer);

    // utility methods
    const Plugin& plugin() const;

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
    std::unique_ptr<AudioScript> m_script;

    Plugin& m_plugin;
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
