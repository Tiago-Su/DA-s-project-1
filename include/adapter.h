#ifndef ADAPTER
#define ADAPTER

#include "Graph.h"
#include "parser.h"
#include <unordered_map>

enum vertexType {
    source,
    sink,
    submission,
    reviewer
};

class Adapter {
  public:
    Graph<int> graph;
    std::unordered_map<int, vertexType> map;
    void convert_to_graph(Parser parser);
};

#endif
