#include "blockarea.h"
#include "plugin.h"
#include "audioblock.h"

BlockArea::BlockArea(QObject* parent)
    : QGraphicsScene(0,0,1,1,parent)
{
    setBackgroundBrush(Qt::white);
}

void BlockArea::onPluginRemoved(Plugin& plugin)
{
    for (auto item : items()) {
        // filter out all but top-level items
        if (!item->parentItem()) {
            // filter items that are not AudioBlocks
            auto block = qgraphicsitem_cast<AudioBlock*>(item);
            // remove AudioBlocks that are based on the current plugin
            if (block && &block->plugin() == &plugin) {
                removeItem(block);
                delete block;
            }
        }
    }
}
