#include "maxFlow.h"

void MaxFlow::testAndVisit(std::queue<Vertex<int>*>& q, Edge<int>* e, Vertex<int>* w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool MaxFlow::findAugmentingPath(Graph<int>* g, Vertex<int>* s, Vertex<int>* t) {
    for (auto v : g->getVertexSet()) v->setVisited(false);

    std::queue<Vertex<int>*> q;
    q.push(s);
    s->setVisited(true);

    while (!q.empty()) {
        Vertex<int>* u = q.front();
        q.pop();

        for (Edge<int>* edge : u->getAdj()) testAndVisit(q, edge, edge->getDest(), edge->getWeight() - edge->getFlow());
        for (Edge<int>* edge : u->getIncoming()) testAndVisit(q, edge, edge->getOrig(), edge->getFlow());
    }

    return t->isVisited();
}

double MaxFlow::findMinResidualAlongPath(Vertex<int>* s, Vertex<int>* t) {
    double f = INF;
    Vertex<int>* u = t;

    while (u != s) {
        if (u == u->getPath()->getDest()) {
            if (u->getPath()->getWeight() - u->getPath()->getFlow() < f) f = u->getPath()->getWeight() - u->getPath()->getFlow();
            u = u->getPath()->getOrig();
        }

        else {
            if (u->getPath()->getFlow() < f) f = u->getPath()->getFlow();
            u = u->getPath()->getDest();
        }
    }

    return f;
}

void MaxFlow::augmentFlowAlongPath(Vertex<int>* s, Vertex<int>* t, double f) {
    Vertex<int>* u = t;
    while (u != s) {
        if (u == u->getPath()->getDest()) {
            u->getPath()->setFlow(u->getPath()->getFlow() + f);
            u = u->getPath()->getOrig();
        }

        else {
            u->getPath()->setFlow(u->getPath()->getFlow() - f);
            u = u->getPath()->getDest();
        }
    }
}

void MaxFlow::edmondsKarp(Graph<int>* g, int source, int target) {
    Vertex<int>* s = g->findVertex(source);
    Vertex<int>* t = g->findVertex(target);

    while (findAugmentingPath(g, s, t)) {
        augmentFlowAlongPath(s, t, findMinResidualAlongPath(s, t));
    }
}
