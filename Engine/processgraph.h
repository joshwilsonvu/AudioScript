#ifndef AS_PROCESSGRAPH_H
#define AS_PROCESSGRAPH_H

#include <vector>

namespace AS {

class Buffer;
class Script;

class ProcessGraph
{
public:
    ProcessGraph();

    void add(Script* script);

    Buffer process(Buffer in);

private:
    std::vector<Script*> m_graph; // basic implementation, TODO branching
};

} // AS

#endif // AS_PROCESSGRAPH_H
