#include "log.h"

#include <QMutex>

namespace AS {

QAtomicPointer<QIODevice> out = nullptr;

Log log()
{
    return Log(out.load());
}

void setLogDestination(QIODevice* out)
{
    AS::out.store(out);
}

} // AS
