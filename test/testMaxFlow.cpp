#include "adapter.h"
#include "maxFlow.h"

struct output {
    int id_orig;
    int id_dest;
    int match;
};

int main(int argc, char* argv[]) {
    if (argc < 2) return -1;

    Parser parser = Parser(argv[1]);
    Adapter adapter = Adapter(parser);

    Graph<int> graph = adapter.graph;
    MaxFlow maxFlow;

    maxFlow.edmondsKarp(&graph, 0, 1);
    std::vector<output> submissions;
    std::vector<output> reviewers;

    for (size_t i = 2; i < graph.getVertexSet().size(); i++) {
        Vertex<int>* v = graph.getVertexSet()[i];

        switch (adapter.map[i]) {
            case submission:
                for (Edge<int>* edge : v->getIncoming()) {
                    Vertex<int>* rev = edge->getOrig();
                    if (edge->getFlow()) submissions.push_back({v->id, rev->id, edge->domain});
                }

                break;

            case reviewer:
                for (Edge<int>* edge : v->getAdj()) {
                    Vertex<int>* sub = edge->getDest();
                    if (edge->getFlow()) reviewers.push_back({v->id, sub->id, edge->domain});
                }
                break;

            default:
                break;
        }
    }

    std::cout << "#SubmissionId,ReviewerId,Match\n";
    for (output out : submissions) {
        std::cout << out.id_orig << " " << out.id_dest << " " << out.match << std::endl;
    }
    std::cout << "#Total: " << submissions.size() << std::endl;

    std::cout << "#ReviewerId,SubmissionId,Match\n";
    for (output out : reviewers) {
        std::cout << out.id_orig << " " << out.id_dest << " " << out.match << std::endl;
    }
    std::cout << "#Total: " << reviewers.size() << std::endl;
}
