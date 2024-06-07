#include <fstream>
#include "gvl.h"

int main() {
    std::ofstream out("out.gv");
    gvl::Graph g("G");
    g.AddGraphProperty("rankdir", "RL");
    g.AddCommonNodeProperty("shape", "box");

    g.AddNode(gvl::NodeId("1"));
    g.AddNode(gvl::NodeId("2"));
    g.AddEdge(gvl::NodeId("1"), gvl::NodeId("2"));
    g.RenderDot(out);
    return 0;
}
