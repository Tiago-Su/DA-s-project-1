#ifndef ADAPTER
#define ADAPTER

#include "Graph.h"
#include "parser.h"
#include <unordered_map>

/**
 * @enum vertexType
 * @brief Represents the type of nodes
 */
enum vertexType {
    source,
    sink,
    submission,
    reviewer
};

/**
 * @class Adapter
 * @brief Class that converts a Parser into a graph
 */
class Adapter {
  public:
	/**
	 * Graph created by the Adapter
	 */
    Graph<int> graph;

	/**
	 * HashMap that maps each node to its type
	 */
    std::unordered_map<int, vertexType> map;

	/**
	 * @brief Converts the parsed .cvs into the corresponding graph
	 * @param parser The parser object which parsed the .csv
	 * @warning Execute the parsing before calling this method
	*/
    void convert_to_graph(Parser parser);
};

#endif
