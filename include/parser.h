#ifndef PARSER
#define PARSER

#include <string>
#include <vector>

struct reviewer {
    int id = -1;
    int primary = -1;
    int secondary = -1;
};

struct submission {
    int id = -1;
    int primary = -1;
    int secondary = -1;
};

struct parameters {
    int minReviews = -1;
    int maxReviews = -1;
    int primaryRev = -1;
    int secondaryRev = -1;
    int primarySub = -1;
    int secondarySub = -1;
};

struct control {
    int gen = -1;
    int risk = -1;
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
