#include <cstring>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

struct reviewer {
    int id;
    int primary;
    int secondary;
};

struct submission {
    int id;
    int primary;
    int secondary;
};

struct parameters {
    int minReviews;
    int maxReviews;
    int primaryRev;
    int secondaryRev;
    int primarySub;
    int secondarySub;
};

struct control {
    int gen;
    int risk;
    std::string output;
};

int read_value(char* word) {
    int value = -1;
    if (word) value = std::atoi(word);

    return value;
}

void parse_line(char* line, submission& s) {
    // Read Id
    s.id = read_value(std::strtok(line, ","));

    // Skipping title, authors and email
    std::strtok(NULL, ",");
    std::strtok(NULL, ",");
    std::strtok(NULL, ",");

    // Read primary
    s.primary = read_value(std::strtok(NULL, ","));

    // Read secondary
    s.secondary = read_value(std::strtok(NULL, ","));
}

void parse(std::ifstream& file, std::vector<submission>& submissions) {
    std::string line;

    std::getline(file, line);
    std::getline(file, line);

    while (line[0] != '#') {
        char buffer[100];
        std::strcpy(buffer, line.c_str());

        submission s;
        parse_line(buffer, s);
        submissions.push_back(s);

        std::getline(file, line);
    }
}

void parse_line(char* line, reviewer& r) {
    // Read Id
    r.id = read_value(std::strtok(line, ","));

    // Skipping name and email
    std::strtok(NULL, ",");
    std::strtok(NULL, ",");

    // Read primary
    r.primary = read_value(std::strtok(NULL, ","));

    // Read secondary
    r.secondary = read_value(std::strtok(NULL, ","));
}

void parse(std::ifstream& file, std::vector<reviewer>& reviewers) {
    std::string line;
    std::getline(file, line);
    std::getline(file, line);

    while (line[0] != '#') {
        char buffer[100];
        std::strcpy(buffer, line.c_str());

        reviewer r;
        parse_line(buffer, r);
        reviewers.push_back(r);

        std::getline(file, line);
    }
}

void parse_line(char* line, parameters& p, int i) {
    std::strtok(line, ",");
    int value = read_value(std::strtok(NULL, ","));

    switch (i) {
        case 0:
            p.minReviews = value;
            break;
        case 1:
            p.maxReviews = value;
            break;
        case 2:
            p.primaryRev = value;
            break;
        case 3:
            p.secondaryRev = value;
            break;
        case 4:
            p.primarySub = value;
            break;
        case 5:
            p.secondarySub = value;
            break;
    }
}

void parse(std::ifstream& file, parameters& parameters) {
    std::string line;
    std::getline(file, line);
    int i = 0;

    while (line[0] != '#') {
        char buffer[100];
        std::strcpy(buffer, line.c_str());
        parse_line(buffer, parameters, i);

        std::getline(file, line);
        i++;
    }
}

void parse_line(char* line, control& p, int i) {
    std::strtok(line, ",");
    char* word = std::strtok(NULL, ",");
    int value = read_value(word);

    switch (i) {
        case 0:
            p.gen = value;
            break;
        case 1:
            p.risk = value;
            break;
        case 2:
			p.output = word;
            break;
    }
}

void parse(std::ifstream& file, control& control) {
    std::string line;
    std::getline(file, line);
    int i = 0;


    while (!line.empty() && line[0] != '#') {
        char buffer[100];
        std::strcpy(buffer, line.c_str());
        parse_line(buffer, control, i);

        std::getline(file, line);
        i++;
    }
}

void parse_file(const char* file, std::vector<submission>& submissions, std::vector<reviewer>& reviewers, parameters& parameters, control& control) {
    std::ifstream in(file);

    std::string line;
    std::getline(in, line);

    parse(in, submissions);
    parse(in, reviewers);
    parse(in, parameters);
	parse(in, control);
}

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
