#include "parser.h"
#include "Graph.h"
#include <unordered_map>

enum vertexType {

    source,
    sink,
    submission,
    reviewer
};

template <class T>
class Adapter{
    public:
        Adapter(Parser parser);
        void convert_to_graph(Parser parser);
        Graph<T> graph;
        std::unordered_map<int, vertexType> map;

        
    private:
};

