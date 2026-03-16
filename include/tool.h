#ifndef TOOL
#define TOOL

#include "parser.h"
#include "adapter.h"
#include "maxFlow.h"

struct output {
    int id_orig;
    int id_dest;
    int match;
};

class Tool {
  public:
	void setup(char* path);
	void get_max_flow();

	char* path = nullptr;
	std::vector<output> reviewers_output;
	std::vector<output> submissions_output;

  private:
	Adapter adapter;
	Parser parser;
	MaxFlow max_flow;
};

#endif
