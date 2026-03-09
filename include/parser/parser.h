#ifndef PARSER
#define PARSER

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

int read_value(char* word);

void parse_line(char* line, submission& s);
void parse_line(char* line, reviewer& r);
void parse_line(char* line, parameters& p, int i);
void parse_line(char* line, control& p, int i);

void parse(std::ifstream& file, std::vector<submission>& submissions);
void parse(std::ifstream& file, std::vector<reviewer>& reviewers);
void parse(std::ifstream& file, parameters& parameters);
void parse(std::ifstream& file, control& control);

std::ifstream find_header(const char* file, const std::string& header);
void parse_file(const char* file, std::vector<submission>& submissions, std::vector<reviewer>& reviewers, parameters& parameters, control& control);

#endif
