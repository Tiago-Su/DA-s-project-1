#include "parser.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) return -1;

    Parser parser = Parser(argv[1]);

    std::cout << "Submissions\n";
    for (submission sub : parser.submissions) std::cout << sub.id << ' ' << sub.primary << ' ' << sub.secondary << std::endl;

    std::cout << "Reviewers\n";
    for (reviewer rev : parser.reviewers) std::cout << rev.id << ' ' << rev.primary << ' ' << rev.secondary << std::endl;

    std::cout << "Parameters\n";
    std::cout << parser.parameters.minReviews << " " << parser.parameters.maxReviews << " " << parser.parameters.primaryRev << " " << parser.parameters.secondaryRev << " " << parser.parameters.primarySub << " " << parser.parameters.secondarySub << std::endl;

    std::cout << "Control\n";
    std::cout << parser.control.gen << " " << parser.control.risk << " " << parser.control.output << std::endl;
    return 0;
}
