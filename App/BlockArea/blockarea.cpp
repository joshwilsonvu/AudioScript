#include "blockarea.h"
#include "audioblock.h"

BlockArea::BlockArea(QObject* parent)
    : QGraphicsScene(0,0,1,1,parent)
{
    setBackgroundBrush(Qt::white);
}
