#ifndef AS_PROCESSGRAPH_H
#define AS_PROCESSGRAPH_H

#include <vector>
#include <QObject>

namespace AS {

class Buffer;
class Script;

class ProcessGraph : public QObject
{
    Q_OBJECT

public:
    ProcessGraph(QObject* parent = nullptr);

    void add(Script* script);

private:
    std::vector<Script*> m_graph; // basic implementation, TODO branching
};

} // AS

#endif // AS_PROCESSGRAPH_H
