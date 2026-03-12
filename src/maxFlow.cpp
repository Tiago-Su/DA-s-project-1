// Original code by Gonçalo Leão
// Updated by DA 2024/2025 Team

#include "maxFlow.h"

// Function to test the given vertex 'w' and visit it if conditions are met
template <class T>
void MaxFlow<T>::testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
    // Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
        // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
template <class T>
bool MaxFlow<T>::findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
    // Mark all vertices as not visited
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    std::queue<Vertex<T>*> q;
    q.push(s);
    s->setVisited(true);

    while(! q.empty()){

        Vertex<T>* u = q.front();
        q.pop();

        for (Edge<T> * edge : u->getAdj()){
            
            testAndVisit(q, edge, edge->getDest(), edge->getWeight() - edge->getFlow());
        }

        for (Edge<T> * edge : u->getIncoming()){

            testAndVisit(q, edge, edge->getOrig(), edge->getFlow());
        }
    
    }
    // Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

// Function to find the minimum residual capacity along the augmenting path
template <class T>
double MaxFlow<T>::findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;

    Vertex<T> * u = t;

    while (u != s){

        if (u == u->getPath()->getDest()) {

            if (u->getPath()->getWeight() - u->getPath()->getFlow() < f) f = u->getPath()->getWeight() - u->getPath()->getFlow();
            u = u->getPath()->getOrig();
        }

        else {
            if (u->getPath()->getFlow() < f) f = u->getPath()->getFlow();
            u = u->getPath()->getDest();
        }
    }

    // Return the minimum residual capacity
    return f;
}

// Function to augment flow along the augmenting path with the given flow value
template <class T>
void MaxFlow<T>::augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f) {
    // Traverse the augmenting path and update the flow values accordingly
    
    Vertex<T> * u = t;

    while (u != s){

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

// Main function implementing the Edmonds-Karp algorithm
template <class T>
void MaxFlow<T>::edmondsKarp(Graph<T> *g, int source, int target) {
    // Find source and target vertices in the graph
    Vertex<T>* s = g->findVertex(source);
    Vertex<T>* t = g->findVertex(target);

   while (findAugmentingPath(g, s, t)) {
       augmentFlowAlongPath(s, t, findMinResidualAlongPath(s, t));
   }

}

template <class T>
MaxFlow<T>::MaxFlow(Graph<T> * graph) : graph (graph){
}