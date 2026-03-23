#ifndef TOOL
#define TOOL

#include "adapter.h"
#include "maxFlow.h"
#include "parser.h"
#include <set>

/**
 * @struct output
 * @brief Stores output info
 */
struct output {
    int id_orig;
    int id_dest;
    int match;
};

class Tool {
  public:

    /**
     * @brief Sets up the graph that is parsed from path
     * @param path String with path to input file
     */
    void setup(char* path);

    /**
     * @brief Runs the max flow algorithm and stores info in reviewers_output and submissions_output attributes
     */
    void get_max_flow();

    /**
     * @brief Stores submissions that have missing reviews in missing_output attribute
     */
    void get_missing_output();

    /**
     * @brief Runs the risk analysis algorithm
     */
    void risk_analysis();

    /**
     * @brief Prints the risk analysis results
     */
    void print_risk_analysis();

    /**
     * @brief Prints the parameters and the control information
     */
    void printParametersControl();

    /**
     * @brief Prints the submissions information
     */
    void printSubmissions();

    /**
     * @brief Prints the reviewers information
     */
    void printReviewers();

    /**
     * @brief Runs BFS algorithm through the graph
     * @param v Vertex to start BFS
     */
    void bfs(Vertex<int>* v);

    /**
     * @brief Resets isVisited attribute of all vertexes in the graph
     */
    void reset_graph();

    /**
     * @brief Prints the output of the algorithm
     */
    void print_output();

    /**
     * @brief Saves the output of the algorithm to a file
     */
    void save_to_file();

    /**
     * @brief Saves the output of the algorithm to param file
     * @param file File to save output into
     */
    void save_to_file(char* file);

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

    /**
     * @brief Prints the submissions, reviewers and total outputs
     */
    void print_basic(std::ostream& output_stream) {
        if (!is_max_flow_done) return;
        output_stream << "#SubmissionId,ReviewerId,Match\n";
        for (output out : submissions_output) output_stream << out.id_orig << ", " << out.id_dest << ", " << out.match << std::endl;

        output_stream << "#ReviewerId,SubmissionId,Match\n";
        for (output out : reviewers_output) output_stream << out.id_orig << ", " << out.id_dest << ", " << out.match << std::endl;
        output_stream << "#Total: " << reviewers_output.size() << std::endl;
    }

    /**
     * @brief Prints the missing submissions output
     */
    void print_missing(std::ostream& output_stream) {
        if (!is_missing_output_done || !missing_output.size()) return;
        output_stream << "#SubmissionId,Domain,MissingReviews\n";
        for (output out : missing_output) output_stream << out.id_orig << ", " << out.id_dest << ", " << out.match << std::endl;
    }

    /**
     * @brief Prints the risk analysis output
     */
    void print_risk(std::ostream& output_stream) {
        if (!is_risk_analysis_done) return;
        output_stream << "#Risk Analysis: " << parser.control.risk << std::endl;
        if (!risk_output.size()) return;

        auto it = risk_output.begin();
        output_stream << *it;

        it++;
        while (it != risk_output.end()) {
            output_stream << ", " << *it;
            it++;
        }

        output_stream << std::endl;
    }
};

#endif
