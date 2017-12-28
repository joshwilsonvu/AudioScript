#include "blockarea.h"

BlockArea::BlockArea(QObject* parent)
    : QGraphicsScene(0,0,1,1,parent)
{
    setBackgroundBrush(Qt::white);
}
