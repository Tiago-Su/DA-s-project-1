#ifndef TOOL
#define TOOL

#include "adapter.h"
#include "maxFlow.h"
#include "parser.h"
#include <set>

struct output {
    int id_orig;
    int id_dest;
    int match;
};

class Tool {
  public:
    void setup(char* path);
    void get_max_flow();
    void get_missing_output();
    void risk_analysis();
    void print_risk_analysis();
    void printParametersControl();
    void printSubmissions();
    void printReviewers();
    void bfs(Vertex<int>* v);
    void reset_graph();

    void print_output();
    char* path = nullptr;
    std::vector<output> reviewers_output;
    std::vector<output> submissions_output;
    std::vector<output> missing_output;
    std::set<int> risk_output;

  private:
    Adapter adapter;
    Parser parser;
    MaxFlow max_flow;

    bool is_setup_done = false;
    bool is_max_flow_done = false;
    bool is_missing_output_done = false;
    bool is_risk_analysis_done = false;

    void print_basic() {
        if (!is_max_flow_done) return;
        std::cout << "#SubmissionId,ReviewerId,Match\n";
        for (output out : submissions_output) std::cout << out.id_orig << ", " << out.id_dest << ", " << out.match << std::endl;

        std::cout << "#ReviewerId,SubmissionId,Match\n";
        for (output out : reviewers_output) std::cout << out.id_orig << ", " << out.id_dest << ", " << out.match << std::endl;
        std::cout << "#Total: " << reviewers_output.size() << std::endl;
    }

    void print_missing() {
        if (!is_missing_output_done || !missing_output.size()) return;
        std::cout << "#SubmissionId,Domain,MissingReviews\n";
        for (output out : missing_output) std::cout << out.id_orig << ", " << out.id_dest << ", " << out.match << std::endl;
    }

    void print_risk() {
        if (!is_risk_analysis_done) return;
        std::cout << "#Risk Analysis: " << parser.control.risk << std::endl;
        if (!risk_output.size()) return;

        auto it = risk_output.begin();
        std::cout << *it;

        it++;
        while (it != risk_output.end()) {
            std::cout << ", " << *it;
            it++;
        }

        std::cout << std::endl;
    }
};

#endif
