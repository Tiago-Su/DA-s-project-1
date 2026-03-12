#include "adapter.h"
#include <iostream>


int main(int argc, char* argv[]) {
    if (argc < 2) return -1;

    Parser parser = Parser(argv[1]);
    Adapter<int> adapter = Adapter<int>(parser);

    Graph<int> graph = adapter.graph;

    for (size_t i = 0; i < graph.getVertexSet().size(); i++) {
        Vertex<int>* v1 = graph.getVertexSet()[i];

        for (size_t j = 0; j < v1->getAdj().size(); j++) {
            std::cout << v1->getAdj()[j]->getOrig()->getInfo() << " " << v1->getAdj()[j]->getDest()->getInfo() << std::endl;
        }
    }
    
    return 0;
}