#include "audioblock.h"

#include <QApplication>
#include <QFontMetrics>
#include <QGraphicsScene>
#include <QPainter>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <QtDebug>

namespace AS {

AudioBlock::AudioBlock(Engine* engine, QString plugin, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_engine(engine), m_plugin(plugin),
      m_next(nullptr), m_prev(nullptr)
{
    m_sz.setY(QApplication::fontMetrics().height() + 2 * k_spacing);
    m_sz.setX(qMax(QApplication::fontMetrics().width(name()) + 2 * k_spacing, (int)m_sz.y()));

    // set graphicsscene flags
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

AudioBlock::~AudioBlock()
{
    unlink();
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

QString AudioBlock::name() const
{
    return m_plugin;
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
    qDebug() << name();
}

void AudioBlock::link(AudioBlock* first, AudioBlock* second)
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

void AudioBlock::unlink()
{
    link(this->prev(), this->next());
}

void AudioBlock::cut()
{
    link(this->prev(), nullptr);
    link(this->next(), nullptr);
}

} // AS
