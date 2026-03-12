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
        
        struct parameters_ {
            int minReviews = -1;
            int maxReviews = -1;
            int primaryRev = -1;
            int secondaryRev = -1;
            int primarySub = -1;
            int secondarySub = -1;
        };
        
        struct control_ {
            int gen = -1;
            int risk = -1;
            std::string output;
        };

class Parser{
    
    public: 

        Parser(const char* filename);
        std::vector<reviewer> reviewers;
        std::vector<submission> submissions;
        parameters_ parameters;
        control_ control;

    private:
        
        
        int read_value(char* word);
        
        void parse_line(char* line, submission& s);
        void parse_line(char* line, reviewer& r);
        void parse_line(char* line, parameters_& p, int i);
        void parse_line(char* line, control_& p, int i);
        
        void parse(std::ifstream& file, std::vector<submission>& submissions);
        void parse(std::ifstream& file, std::vector<reviewer>& reviewers);
        void parse(std::ifstream& file, parameters_& parameters);
        void parse(std::ifstream& file, control_& control);
        
        std::ifstream find_header(const char* file, const std::string& header);
        void parse_file(const char* file, std::vector<submission>& submissions, std::vector<reviewer>& reviewers, parameters_& parameters, control_& control);

};



#endif
