#include "Graph.h"
#include <limits>

// Function to perform DFS and find an augmenting path
template <class T>
bool dfsFindAugmentingPath(Vertex<T>* v, Vertex<T>* t, double& flow) {
    if (v == t) return true;
    v->setVisited(true);

    for (size_t i = 0; i < v->getAdj().size(); i++) {
        Edge<T>* edge = v->getAdj()[i];
        Vertex<T>* next = edge->getDest();

        double old = flow;
        if (!next->isVisited() && edge->getWeight() - edge->getFlow() != 0) {
            flow = std::min(flow, edge->getWeight() - edge->getFlow());
			next->setPath(edge);
            if (dfsFindAugmentingPath(next, t, flow)) return true;
        }
        flow = old;
		next -> setVisited(false);
    }

    for (size_t i = 0; i < v->getIncoming().size(); i++) {
        Edge<T>* edge = v->getIncoming()[i];
        Vertex<T>* next = edge->getOrig();

        double old = flow;
        if (!next->isVisited() && edge->getFlow() != 0) {
            flow = std::min(flow, edge->getFlow());
			next->setPath(edge);
            if (dfsFindAugmentingPath(next, t, flow)) return true;
        }
        flow = old;
		next -> setVisited(false);
    }

    return false;
}

// Ford-Fulkerson algorithm
template <class T>
void fordFulkerson(Graph<T>* g, int source, int target) {
    Vertex<T>* s = g->findVertex(source);
    Vertex<T>* t = g->findVertex(target);

    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");

    for (size_t i = 0; i < g->getVertexSet().size(); i++) {
        Vertex<T>* v = g->getVertexSet()[i];
        v->setVisited(false);

        for (size_t j = 0; j < v->getAdj().size(); j++) {
            v->getAdj()[j]->setFlow(0);
        }
    }

    double f = INF;
    while (dfsFindAugmentingPath(s, t, f)) {
        Vertex<T>* current = t;

        while (s->getInfo() != current->getInfo()) {
            Edge<T>* edge = current->getPath();
            double currentFlow = edge->getFlow();

            if (edge->getDest()->getInfo() == current->getInfo()) {
                edge->setFlow(edge->getFlow() + f);
                current = edge->getOrig();
            } else {
                edge->setFlow(edge->getFlow() - f);
                current = edge->getDest();
            }
        }

        for (size_t i = 0; i < g->getVertexSet().size(); i++) {
            Vertex<T>* v = g->getVertexSet()[i];
            v->setVisited(false);
        }

        f = INF;
    }
}
