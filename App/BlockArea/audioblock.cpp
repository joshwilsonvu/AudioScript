#include "audioblock.h"
#include "audioscript.h"

#include <QApplication>
#include <QFontMetrics>
#include <QPainter>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <QtDebug>

AudioBlock::AudioBlock(AudioScriptPlugin& library, QGraphicsItem* parent)
    : AudioBlock(library, Q_NULLPTR, Q_NULLPTR, parent)
{}

AudioBlock::AudioBlock(AudioScriptPlugin& library,
           AudioBlock* prev, AudioBlock* next, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_script(Q_NULLPTR), m_plugin(library),
      m_next(Q_NULLPTR), m_prev(Q_NULLPTR)
{
    link(this, next);
    link(prev, this);

    m_sz.setY(QApplication::fontMetrics().height() + 2 * k_spacing);
    m_sz.setX(qMin(QApplication::fontMetrics().width(name()) + 2 * k_spacing, (int)m_sz.y()));

    if (m_plugin.spawnable()) {
        m_script = m_plugin.spawn(); // generate script, owned
    }


}

AudioBlock::~AudioBlock()
{
    unlink(this);
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
    qreal penw = 1.f;
    // shrink drawing area for pen width
    rect.adjust(0.5f*penw,0.5f*penw, -0.5f*penw, -0.5f*penw);
    painter->setBrush(Qt::lightGray);
    painter->setPen(QPen(Qt::black, penw));
    painter->drawRoundedRect(rect, k_spacing, k_spacing);
    painter->drawText(rect, name(), QTextOption(Qt::AlignCenter));
}

sample_t AudioBlock::process(sample_t sample)
{
    return m_script ? m_script->process(sample) : 0.f;
}

QString AudioBlock::name() const
{
    return m_plugin.name();
}


QString AudioBlock::info() const
{
    return m_plugin.info();
}


const AudioScriptPlugin& AudioBlock::library() const
{
    return m_plugin;
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

void AudioBlock::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    // TODO make real implementation
    Q_UNUSED(event);
    qDebug() << name() << ":" << info();
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
