#include "adapter.h"
#include <unordered_set>

void Adapter::convert_to_graph(Parser parser) {
    std::unordered_map<int, std::vector<int>> reviewersExpertise;

    graph.addVertex(0);
    graph.getVertexSet()[0]->id = -1;
    map[0] = source;

    graph.addVertex(1);
    graph.getVertexSet()[1]->id = -2;
    map[1] = sink;

    for (size_t i = 2; i < parser.reviewers.size() + 2; i++) {
        // Creating a vertex for each reviewer and adding the edge from source to reviewer
        graph.addVertex(i);
        graph.getVertexSet()[i]->id = parser.reviewers[i - 2].id;
        map[i] = reviewer;
        graph.addEdge(0, i, parser.parameters.maxReviews, -1);

        if (parser.parameters.primaryRev) reviewersExpertise[parser.reviewers[i - 2].primary].push_back(i);
        if (parser.parameters.secondaryRev) reviewersExpertise[parser.reviewers[i - 2].secondary].push_back(i);
    }

    // Removing all expertises without a valid value
    reviewersExpertise[-1].clear();

    for (size_t i = 2 + parser.reviewers.size(); i < 2 + parser.reviewers.size() + parser.submissions.size(); i++) {
        // Creating a vertex for each submission
        graph.addVertex(i);
        graph.getVertexSet()[i]->id = parser.submissions[i - 2 - parser.reviewers.size()].id;
        map[i] = submission;
        graph.addEdge(i, 1, parser.parameters.minReviews, parser.submissions[i - 2 - parser.reviewers.size()].primary);

        std::unordered_set<int> seen;
        // Adding the edge from reviewer to submission - primary topic
        if (parser.parameters.primarySub) {
            int primary = parser.submissions[i - 2 - parser.reviewers.size()].primary;

            for (int vertexid : reviewersExpertise[primary]) {
                graph.addEdge(vertexid, i, 1, primary);
                seen.insert(vertexid);
            }
        }

        // Ading the edge from reviewer to submission - secondary topic
        if (parser.parameters.secondarySub) {
            int secondary = parser.submissions[i - 2 - parser.reviewers.size()].secondary;

            for (int vertexid : reviewersExpertise[secondary]) {
                if (seen.find(vertexid) == seen.end()) graph.addEdge(vertexid, i, 1, secondary);
            }
        }
    }
}
