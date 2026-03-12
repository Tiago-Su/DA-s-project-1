#ifndef ADAPTER
#define ADAPTER

#include "parser.h"
#include "Graph.h"
#include <unordered_map>

enum vertexType {

    source,
    sink,
    submission,
    reviewer
};


class Adapter{
    public:
        Adapter(Parser parser){
            convert_to_graph(parser);
        }
        void convert_to_graph(Parser parser);
        Graph<int> graph;
        std::unordered_map<int, vertexType> map;

        
    private:
};

#endif