#include "maxFlow.h"

template <class T>
void MaxFlow<T>::testAndVisit(std::queue<Vertex<T>*>& q, Edge<T>* e, Vertex<T>* w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

template <class T>
bool MaxFlow<T>::findAugmentingPath(Graph<T>* g, Vertex<T>* s, Vertex<T>* t) {
    for (auto v : g->getVertexSet()) v->setVisited(false);

    std::queue<Vertex<T>*> q;
    q.push(s);
    s->setVisited(true);

    while (!q.empty()) {
        Vertex<T>* u = q.front();
        q.pop();

        for (Edge<T>* edge : u->getAdj()) testAndVisit(q, edge, edge->getDest(), edge->getWeight() - edge->getFlow());
        for (Edge<T>* edge : u->getIncoming()) testAndVisit(q, edge, edge->getOrig(), edge->getFlow());
    }

    return t->isVisited();
}

template <class T>
double MaxFlow<T>::findMinResidualAlongPath(Vertex<T>* s, Vertex<T>* t) {
    double f = INF;
    Vertex<T>* u = t;

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

template <class T>
void MaxFlow<T>::augmentFlowAlongPath(Vertex<T>* s, Vertex<T>* t, double f) {
    Vertex<T>* u = t;
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

template <class T>
void MaxFlow<T>::edmondsKarp(Graph<T>* g, int source, int target) {
    Vertex<T>* s = g->findVertex(source);
    Vertex<T>* t = g->findVertex(target);

    while (findAugmentingPath(g, s, t)) augmentFlowAlongPath(s, t, findMinResidualAlongPath(s, t));
}
