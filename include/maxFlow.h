#ifndef MAXFLOW
#define MAXFLOW

#include"Graph.h"

template <class T>
class MaxFlow{

    public:

    MaxFlow(Graph<T> * graph);
    void edmondsKarp(Graph<T> *g, int source, int target);

    private:

    void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual);
    bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t);
    double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t);
    void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f);

};

#endif