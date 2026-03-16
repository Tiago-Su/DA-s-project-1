#include "maxFlow.h"
#include "adapter.h"

struct output
{
    int id_orig;
    int id_dest;
    int match;
};


int main(int argc, char * argv[]){

    if (argc < 2) return -1;

    Parser parser = Parser(argv[1]);
    Adapter adapter = Adapter(parser);

    Graph<int> graph = adapter.graph;

    MaxFlow<int>::edmondsKarp(&graph, 1, 2);

    std::vector<output> submissions;
    std::vector<output> reviewers;

    for (int i = 2; i <= graph.getNumVertex(); i++){
        Vertex<int> * v = graph.getVertexSet()[i];

        switch (adapter.map[i])
        {
        case submission:

            for(Edge<int>* edge : v->getIncoming()){

                Vertex<int>* rev = edge->getOrig();
                if (edge->getFlow()) submissions.push_back({v->id, rev->id, edge->domain});
            }
            
            break;
        
            case reviewer:
            
            for(Edge<int>* edge : v->getAdj()){

                Vertex<int>* sub = edge->getDest();
                if (edge->getFlow()) reviewers.push_back({v->id, sub->id, edge->domain});
            }
            break;
        
        default:
            break;
        }
    }

    for (output out : submissions){
        std::cout << out.id_orig << " " << out.id_dest << " " << out.match << std::endl;
    }
    for (output out : reviewers){
        std::cout << out.id_orig << " " << out.id_dest << " " << out.match << std::endl;
    }
}