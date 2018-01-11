#include "audioblock.h"
#include "audioscript.h"
#include "audioscriptbuffer.h"

#include <QApplication>
#include <QFontMetrics>
#include <QPainter>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <QtDebug>

AudioBlock::AudioBlock(AudioScriptPlugin& library, QGraphicsItem* parent)
    : AudioBlock(library, nullptr, nullptr, parent)
{}

AudioBlock::AudioBlock(AudioScriptPlugin& library,
           AudioBlock* prev, AudioBlock* next, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_script(nullptr), m_plugin(library),
      m_next(nullptr), m_prev(nullptr)
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

AudioScriptBuffer AudioBlock::process(AudioScriptBuffer buffer)
{
    if (m_script) {
        try {
            return m_script->process(buffer);
        } catch (...) {
            qDebug() << "AudioScript" << name() << "threw an exception.";
        }
    }
    return AudioScriptBuffer(0);
}

QString AudioBlock::name() const
{
    return m_plugin.name();
}


QString AudioBlock::info() const
{
    return m_plugin.info();
}


const AudioScriptPlugin& AudioBlock::plugin() const
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
            first->m_next->m_prev = nullptr;
        }
        first->m_next = second;
    }
    if (second) {
        if (second->m_prev) {
            second->m_prev->m_next = nullptr;
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
        link(block->prev(), nullptr);
        link(block->next(), nullptr);
    }
}
