#ifndef BLOCKAREA_H
#define BLOCKAREA_H

#include <QGraphicsScene>

class Plugin;

class BlockArea : public QGraphicsScene
{
    Q_OBJECT

public:
    BlockArea(QObject* parent = nullptr);

public slots:
    void onPluginRemoved(Plugin& plugin);
};

#endif // BLOCKAREA_H
