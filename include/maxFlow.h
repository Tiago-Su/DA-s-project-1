#ifndef MAXFLOW
#define MAXFLOW

#include "Graph.h"

/**
 * @class MaxFlow
 * @brief Class that executes EdmondsKarp maximum flow algorithm
 */
class MaxFlow {
  public:
	/**
	* @brief Method that executes the EdmondsKarp maximum flow algorithm
	* @param g Graph to be applied the algorithm
	* @param source The source node
	* @param target The sink node
	*/
    void edmondsKarp(Graph<int>* g, int source, int target);

  private:
	/**
	* @brief Method that finds an augmenting path from source to sink. The found path is stored in node's path
	* @param g Graph to find an augmenting path
	* @param s Source node
	* @param t Sink node
	* @return Return true if found an augmenting path from source to sink
	*/
    bool findAugmentingPath(Graph<int>* g, Vertex<int>* s, Vertex<int>* t);

	/**
	* @brief Method that finds the minimum residual value from the augmenting path found
	* @param s Source node
	* @param t Sink node
	* @return The minimum residual value found in the augmenting path
	*/
    double findMinResidualAlongPath(Vertex<int>* s, Vertex<int>* t);

	/**
	* @brief Method that updates the residual graph
	* @param s Source node
	* @param t Sink node
	* @param f Flow
	*/
    void augmentFlowAlongPath(Vertex<int>* s, Vertex<int>* t, double f);
};

#endif
