#include "adapter.h"
#include <iostream>


int main(int argc, char* argv[]) {
    if (argc < 2) return -1;

    Parser parser;
    Adapter adapter;

	parser.load_file(argv[1]);
	parser.parse_file();

	adapter.convert_to_graph(parser);
    Graph<int> graph = adapter.graph;

    for (size_t i = 0; i < graph.getVertexSet().size(); i++) {
        Vertex<int>* v1 = graph.getVertexSet()[i];

        for (size_t j = 0; j < v1->getAdj().size(); j++) {
            std::cout << v1->getAdj()[j]->getOrig()->id << " " << v1->getAdj()[j]->getDest()->id   << " " << v1->getAdj()[j]->domain << " " << v1->getAdj()[j]->getWeight() << std::endl;
        }
    }
    
    return 0;
}
