#include "parser/parser.h"
#include <cstring>
#include <fstream>
#include <stdio.h>

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

    while (file && line[0] != '#') {
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

    while (file && line[0] != '#') {
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

    while (file && line[0] != '#') {
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


    while (file && line[0] != '#') {
        char buffer[100];
        std::strcpy(buffer, line.c_str());
        parse_line(buffer, control, i);

        std::getline(file, line);
        i++;
    }
}

std::ifstream find_header(const char* file, const std::string& header) {	
	std::ifstream in(file);
	std::string line;
	std::getline(in, line);

	while (in && line != header) {
		std::getline(in, line);
	}

	return in;
}

void parse_file(const char* file, std::vector<submission>& submissions, std::vector<reviewer>& reviewers, parameters& parameters, control& control) {
	std::ifstream in;

	in = find_header(file, "#Submissions");
    parse(in, submissions);

	in = find_header(file, "#Reviewers");
    parse(in, reviewers);

	in = find_header(file, "#Parameters");
    parse(in, parameters);

	in = find_header(file, "#Control");
	parse(in, control);
}
