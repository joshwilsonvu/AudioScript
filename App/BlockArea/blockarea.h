#ifndef BLOCKAREA_H
#define BLOCKAREA_H

#include <QGraphicsScene>

class BlockArea : public QGraphicsScene
{
    Q_OBJECT

public:
    BlockArea(QObject* parent = Q_NULLPTR);
};

#endif // BLOCKAREA_H
