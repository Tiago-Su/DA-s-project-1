#include "adapter.h"
#include <unordered_set>

void Adapter::convert_to_graph(Parser parser) {
    std::unordered_map<int, std::vector<int>> reviewersExpertise;

    graph.addVertex(1);
    map[1] = source;

    graph.addVertex(2);
    map[2] = sink;

    for (size_t i = 3; i < parser.reviewers.size() + 3; i++) {
        // Creating a vertex for each reviewer and adding the edge from source to reviewer
        graph.addVertex(i);
        map[i] = reviewer;
        graph.addEdge(1, i, parser.parameters.maxReviews);

        if (parser.parameters.primaryRev) reviewersExpertise[parser.reviewers[i - 3].primary].push_back(i);
        if (parser.parameters.secondaryRev) reviewersExpertise[parser.reviewers[i - 3].secondary].push_back(i);
    }

    // Removing all expertises without a valid value
    reviewersExpertise[-1].clear();

    for (size_t i = 3 + parser.reviewers.size(); i < 3 + parser.reviewers.size() + parser.submissions.size(); i++) {
        // Creating a vertex for each submission
        graph.addVertex(i);
        map[i] = submission;
        graph.addEdge(i, 2, parser.parameters.minReviews);

        std::unordered_set<int> seen;
        // Adding the edge from reviewer to submission - primary topic
        if (parser.parameters.primarySub) {
            int primary = parser.submissions[i - 3 - parser.reviewers.size()].primary;

            for (int vertexid : reviewersExpertise[primary]) {
                graph.addEdge(vertexid, i, 1);
                seen.insert(vertexid);
            }
        }

        // Ading the edge from reviewer to submission - secondary topic
        if (parser.parameters.secondarySub) {
            int secondary = parser.submissions[i - 3 - parser.reviewers.size()].secondary;

            for (int vertexid : reviewersExpertise[secondary]) {
                if (seen.find(vertexid) == seen.end()) graph.addEdge(vertexid, i, 1);
            }
        }
    }
}
