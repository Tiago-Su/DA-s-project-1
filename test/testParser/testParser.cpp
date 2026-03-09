#include "parser/parser.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) return -1;

    std::vector<submission> submissions;
    std::vector<reviewer> reviewers;
    parameters paramenters;
    control control;

    parse_file(argv[1], submissions, reviewers, paramenters, control);

    std::cout << "Submissions\n";
    for (submission sub : submissions) std::cout << sub.id << ' ' << sub.primary << ' ' << sub.secondary << std::endl;

    std::cout << "Reviewers\n";
    for (reviewer rev : reviewers) std::cout << rev.id << ' ' << rev.primary << ' ' << rev.secondary << std::endl;

    std::cout << "Parameters\n";
    std::cout << paramenters.minReviews << " " << paramenters.maxReviews << " " << paramenters.primaryRev << " " << paramenters.secondaryRev << " " << paramenters.primarySub << " " << paramenters.secondarySub << std::endl;

    std::cout << "Control\n";
    std::cout << control.gen << " " << control.risk << " " << control.output << std::endl;
    return 0;
}
