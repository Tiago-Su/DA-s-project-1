#include "Graph.h"
#include "maxFlow.h"

bool MaxFlow::findAugmentingPath(Graph<int>* g, Vertex<int>* s, Vertex<int>* t) {
    // Mark all vertices as not visited
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    std::queue<Vertex<int>*> queue;
    queue.push(s);
    s->setVisited(true);

    while (!queue.empty()) {
        Vertex<int>* current = queue.front();
        queue.pop();

        if (current->getInfo() == t->getInfo()) {
            break;
        }

        for (size_t i = 0; i < current->getAdj().size(); i++) {
            Edge<int>* edge = current->getAdj()[i];
            Vertex<int>* next = edge->getDest();

            if (!next->isVisited() && edge->getWeight() - edge->getFlow() != 0) {
                next->setVisited(true);
                next->setPath(edge);
                queue.push(next);
            }
        }

        for (size_t i = 0; i < current->getIncoming().size(); i++) {
            Edge<int>* edge = current->getIncoming()[i];
            Vertex<int>* next = edge->getOrig();

            if (!next->isVisited() && edge->getFlow() != 0) {
                next->setVisited(true);
                next->setPath(edge);
                queue.push(next);
            }
        }
    }

    // Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

double MaxFlow::findMinResidualAlongPath(Vertex<int>* s, Vertex<int>* t) {
    double f = INF;
    Vertex<int>* current = t;

    while (current->getInfo() != s->getInfo()) {
        Edge<int>* edge = current->getPath();

        if (edge->getDest()->getInfo() == current->getInfo()) {
            f = std::min(f, edge->getWeight() - edge->getFlow());
            current = current->getPath()->getOrig();

        } else {
            f = std::min(f, edge->getFlow());
            current = current->getPath()->getDest();
        }
    }

    // Return the minimum residual capacity
    return f;
}

void MaxFlow::augmentFlowAlongPath(Vertex<int>* s, Vertex<int>* t, double f) {
    // Traverse the augmenting path and update the flow values accordingly

    Vertex<int>* current = t;
    while (s->getInfo() != current->getInfo()) {
        Edge<int>* edge = current->getPath();
        double currentFlow = edge->getFlow();

        if (edge->getDest()->getInfo() == current->getInfo()) {
            edge->setFlow(edge->getFlow() + f);
            current = edge->getOrig();
        } else {
            edge->setFlow(edge->getFlow() - f);
            current = edge->getDest();
        }
    }
}

// Main function implementing the Edmonds-Karp algorithm
void MaxFlow::edmondsKarp(Graph<int>* g, int source, int target) {
    // Find source and target vertices in the graph
    Vertex<int>* s = g->findVertex(source);
    Vertex<int>* t = g->findVertex(target);

    for (size_t i = 0; i < g->getVertexSet().size(); i++) {
        Vertex<int>* v = g->getVertexSet()[i];
        for (size_t j = 0; j < v->getAdj().size(); j++) {
            v->getAdj()[j]->setFlow(0);
        }
    }

    while (findAugmentingPath(g, s, t)) {
        double residual = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, residual);
    }
}

