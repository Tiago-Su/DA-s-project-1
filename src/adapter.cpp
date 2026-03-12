#include "adapter.h"
#include <unordered_set>


void Adapter::convert_to_graph(Parser parser){
  
    std::unordered_map<int, std::vector<int>> reviewers_expertise;

    graph.addVertex(1);
    map[1] = source;
    
    graph.addVertex(2);
    map[2] = sink;

    for(int i = 3; i < parser.reviewers.size() + 3; i++){
        graph.addVertex(i);
        map[i] = reviewer;
        graph.addEdge(1, i, parser.parameters.maxReviews);
        
        if (parser.parameters.primaryRev) reviewers_expertise[parser.reviewers[i - 3].primary].push_back(i);
        if (parser.parameters.secondaryRev) reviewers_expertise[parser.reviewers[i - 3].secondary].push_back(i);

    }
reviewers_expertise[-1].clear();


    for(int i = 3 + parser.reviewers.size(); i < parser.reviewers.size() + parser.submissions.size() + 3; i++){
        graph.addVertex(i);
        map[i] = submission;
        graph.addEdge(i, 2, parser.parameters.minReviews);

        std::unordered_set<int> seen;

        if (parser.parameters.primarySub){
            int primary = parser.submissions[i - 3 - parser.reviewers.size()].primary;

            for (int vertexid : reviewers_expertise[primary]){
                graph.addEdge(vertexid, i, 1);
                seen.insert(vertexid);
            } 
        }
        if (parser.parameters.secondarySub) {
            int secondary = parser.submissions[i - 3 - parser.reviewers.size()].secondary;

            for (int vertexid : reviewers_expertise[secondary])  if (seen.find(vertexid) == seen.end()) graph.addEdge(vertexid, i, 1);
        }

    }

}


