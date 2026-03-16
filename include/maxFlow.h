#ifndef MAXFLOW
#define MAXFLOW

#include "Graph.h"

class MaxFlow {
  public:
    void edmondsKarp(Graph<int>* g, int source, int target);

  private:
    void testAndVisit(std::queue<Vertex<int>*>& q, Edge<int>* e, Vertex<int>* w, double residual);
    bool findAugmentingPath(Graph<int>* g, Vertex<int>* s, Vertex<int>* t);
    double findMinResidualAlongPath(Vertex<int>* s, Vertex<int>* t);
    void augmentFlowAlongPath(Vertex<int>* s, Vertex<int>* t, double f);
};

#endif
