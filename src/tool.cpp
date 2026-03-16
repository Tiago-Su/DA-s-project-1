#include "tool.h"

void Tool::setup(char* path) {
	this->path = path;

    parser.load_file(path);
    parser.parse_file();
    adapter.convert_to_graph(parser);
}

void Tool::get_max_flow() {
	if (!path) return;

    max_flow.edmondsKarp(&adapter.graph, 0, 1);
    Graph<int> graph = adapter.graph;

    for (size_t i = 2; i < graph.getVertexSet().size(); i++) {
        Vertex<int>* v = graph.getVertexSet()[i];

        switch (adapter.map[i]) {
            case submission:
                for (Edge<int>* edge : v->getIncoming()) {
                    Vertex<int>* rev = edge->getOrig();
                    if (edge->getFlow()) submissions_output.push_back({v->id, rev->id, edge->domain});
                }
                break;

            case reviewer:
                for (Edge<int>* edge : v->getAdj()) {
                    Vertex<int>* sub = edge->getDest();
                    if (edge->getFlow()) reviewers_output.push_back({v->id, sub->id, edge->domain});
                }
                break;

            default:
                break;
        }
    }
}
