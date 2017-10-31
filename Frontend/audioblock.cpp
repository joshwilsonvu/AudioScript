#include "audioblock.h"
#include "audioscript.h"

#include <QPainter>
#include <QPointF>
#include <QStyleOptionGraphicsItem>

AudioBlock::AudioBlock(AudioScript* script, QGraphicsItem* parent)
    : AudioBlock(script, Q_NULLPTR, Q_NULLPTR, parent)
{
}

AudioBlock::AudioBlock(AudioScript* script, AudioBlock* prev, AudioBlock* next, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_script(script), m_sz()
{
    link(this, next);
    link(prev, this);
}

AudioBlock::~AudioBlock()
{
    // owns AudioScript instance
    link(prev(), Q_NULLPTR);

    delete m_script;
}

QRectF AudioBlock::boundingRect() const
{
    return QRectF(-0.5f * m_sz, 0.5f * m_sz);
}

void AudioBlock::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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

AudioScript* AudioBlock::script() const
{
    return m_script;
}

AudioBlock* AudioBlock::next() const
{
    return m_next;
}

AudioBlock* AudioBlock::prev() const
{
    return m_prev;
}

void AudioBlock::link(AudioBlock* first, AudioBlock* second)
{
    if (first) {
        if (first->m_next) {
            first->m_next->m_prev = Q_NULLPTR;
        }
        first->m_next = second;
    }
    if (second) {
        if (second->m_prev) {
            second->m_prev->m_next = Q_NULLPTR;
        }
        second->m_prev = first;
    }
}

void unlink(AudioBlock* block)
{
    if (block) {
        link(block->prev(), block->next());
    }
}

void cut(AudioBlock *block)
{
    if (block) {
        link(block->prev(), Q_NULLPTR);
        link(block->next(), Q_NULLPTR);
    }
}
