#include "processgraph.h"

#include "script.h"
#include "buffer.h"

namespace AS {

ProcessGraph::ProcessGraph(QObject* parent)
    : QObject(parent)
{

}

void ProcessGraph::add(Script* script)
{
    m_graph.push_back(script);
}

Buffer ProcessGraph::process(Buffer in)
{
    for (auto script : m_graph) {
        in = script->process(std::move(in));
    }
    return in;
}



}
