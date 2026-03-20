#include "tool.h"
#include "Graph.h"
#include <algorithm>
#include <fstream>

bool output_comp(output& a, output& b) {
    return a.id_orig < b.id_orig;
}

void Tool::setup(char* path) {
    this->path = path;
    parser.load_file(path);
    parser.parse_file();
    adapter.convert_to_graph(parser);
    is_setup_done = true;
}

void Tool::get_missing_output() {
    // Storing the missing ones
    for (size_t i = 0; i < adapter.graph.getVertexSet()[1]->getIncoming().size(); i++) {
        Edge<int>* edge = adapter.graph.getVertexSet()[1]->getIncoming()[i];

        if (edge->getFlow() != edge->getWeight()) {
            missing_output.push_back({edge->getOrig()->id, edge->domain, (int)(edge->getWeight() - edge->getFlow())});
        }
    }

    std::sort(missing_output.begin(), missing_output.end(), output_comp);
    is_missing_output_done = true;
}

void Tool::get_max_flow() {
    if (!path || !is_setup_done) {
        printf("Error: load setup dataset first\n");
        return;
    }

    max_flow.edmondsKarp(&adapter.graph, 0, 1);
    Graph<int> graph = adapter.graph;

    // Storing the matchings
    for (size_t i = 2; i < graph.getVertexSet().size(); i++) {
        Vertex<int>* v = graph.getVertexSet()[i];

        switch (adapter.map[i]) {
            case submission:
                for (Edge<int>* edge : v->getIncoming()) {
                    Vertex<int>* rev = edge->getOrig();
                    if (edge->getFlow()) submissions_output.push_back({v->id, rev->id, edge->domain});
                }
                break;

            case reviewer:
                for (Edge<int>* edge : v->getAdj()) {
                    Vertex<int>* sub = edge->getDest();
                    if (edge->getFlow()) reviewers_output.push_back({v->id, sub->id, edge->domain});
                }
                break;

            default:
                break;
        }
    }

    // Sorting
    std::sort(reviewers_output.begin(), reviewers_output.end(), output_comp);
    std::sort(submissions_output.begin(), submissions_output.end(), output_comp);

    is_max_flow_done = true;
}

void Tool::reset_graph() {
    Graph<int>* g = &adapter.graph;
    for (size_t i = 0; i < g->getVertexSet().size(); i++) g->getVertexSet()[i]->setVisited(false);
}

void Tool::bfs(Vertex<int>* v) {
    std::queue<Vertex<int>*> queue;
    reset_graph();

    queue.push(v);
    v->setVisited(true);

    while (!queue.empty()) {
        Vertex<int>* current = queue.front();
        queue.pop();

        for (size_t i = 0; i < current->getAdj().size(); i++) {
            Edge<int>* edge = current->getAdj()[i];
            Vertex<int>* next = edge->getDest();

            if (!next->isVisited() && edge->getWeight() - edge->getFlow()) {
                queue.push(next);
                next->setVisited(true);
            }
        }

        for (size_t i = 0; i < current->getIncoming().size(); i++) {
            Edge<int>* edge = current->getIncoming()[i];
            Vertex<int>* next = edge->getOrig();

            if (!next->isVisited() && edge->getFlow()) {
                queue.push(next);
                next->setVisited(true);
            }
        }
    }
}

void Tool::risk_analysis() {
    if (parser.control.risk != 1) {
		std::cout << "Cannot do risk analysis: risk analysis != 1\n";
		return;
	} 

	if (!missing_output.empty()) {
		std::cout << "Cannot do risk analysis: this dataset is not valid\n";
		return;
	}

    bfs(adapter.graph.getVertexSet()[0]);
    Graph<int>* g = &adapter.graph;

    for (size_t i = 0; i < g->getVertexSet().size(); i++) {
        Vertex<int>* v = g->getVertexSet()[i];
        if (v->isVisited()) continue;

        for (size_t j = 0; j < v->getIncoming().size(); j++) {
            if (adapter.map[v->getInfo()] == submission) {
                risk_output.insert(v->getIncoming()[j]->getOrig()->id);
            }
        }
    }

    is_risk_analysis_done = true;
}

void Tool::printParametersControl() {
    std::cout << "Parameters\n";
    std::cout << parser.parameters.minReviews << " " << parser.parameters.maxReviews << " " << parser.parameters.primaryRev << " " << parser.parameters.secondaryRev << " " << parser.parameters.primarySub << " " << parser.parameters.secondarySub << std::endl;
    std::cout << std::endl;
    std::cout << "Control\n";
    std::cout << parser.control.gen << " " << parser.control.risk << " " << parser.control.output << std::endl;
}

void Tool::printSubmissions() {
    std::cout << "Submissions\n";
    for (auto sub : parser.submissions) std::cout << sub.id << ' ' << sub.primary << ' ' << sub.secondary << std::endl;
}

void Tool::printReviewers() {
    std::cout << "Reviewers\n";
    for (auto rev : parser.reviewers) std::cout << rev.id << ' ' << rev.primary << ' ' << rev.secondary << std::endl;
}

void Tool::save_to_file(){
    std::string file_path = "program_output/" + parser.control.output;
    std::ofstream file_stream(file_path);
	if (file_stream.fail()) {
		std::cout << "An error occurred. Check if directory 'program_ouput' is valid\n";
		return;
	}

	if (!is_missing_output_done) get_missing_output();
	if (parser.control.risk == 1 && !is_risk_analysis_done) risk_analysis();

    print_basic(file_stream);
    print_missing(file_stream);
    print_risk(file_stream);
	file_stream.close();
	std::cout << "Saved successfully\n";
}

void Tool::print_output() {
	print_basic(std::cout);
	print_missing(std::cout);
	print_risk(std::cout);
}

void Tool::print_risk_analysis() {
    print_risk(std::cout);
}
