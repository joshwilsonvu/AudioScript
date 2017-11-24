#include "audioblock.h"
#include "audioscript.h"

#include <QApplication>
#include <QFontMetrics>
#include <QPainter>
#include <QPointF>
#include <QStyleOptionGraphicsItem>

AudioBlock::AudioBlock(AudioScript* script, AudioScriptLibrary* library, QGraphicsItem* parent)
    : AudioBlock(script, library, Q_NULLPTR, Q_NULLPTR, parent)
{

}

AudioBlock::AudioBlock(AudioScript* script, AudioScriptLibrary* library,
           AudioBlock* prev, AudioBlock* next, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_script(script), m_library(library),
      m_next(Q_NULLPTR), m_prev(Q_NULLPTR)
{
    link(this, next);
    link(prev, this);

    m_sz = QPointF(QApplication::fontMetrics().width(name()) + 2 * k_spacing,
                       QApplication::fontMetrics().height() + 2 * k_spacing);
}

AudioBlock::~AudioBlock()
{
    // owns AudioScript instance
    unlink(this);
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
    painter->drawRoundedRect(rect, k_spacing, k_spacing);
    painter->drawText(rect, name(), QTextOption(Qt::AlignCenter));
}

typename AudioBlock::sample_t AudioBlock::process(typename AudioBlock::sample_t sample)
{
    return m_script ? m_script->process(sample) : sample;
}

QString AudioBlock::name() const
{
    return m_library ? m_library->name() : "UNNAMED";
}

AudioScript* AudioBlock::script() const
{
    return m_script.get();
}

AudioBlock* AudioBlock::next() const
{
    return m_next;
}

AudioBlock* AudioBlock::prev() const
{
    return m_prev;
}

void link(AudioBlock* first, AudioBlock* second)
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
