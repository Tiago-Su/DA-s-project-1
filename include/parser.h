#ifndef PARSER
#define PARSER

#include <string>
#include <vector>

/**
 * @struct reviewer
 * @brief Stores info of each reviewer
 */
struct reviewer {
    int id = -1;
    int primary = -1;
    int secondary = -1;
};

/**
 * @struct submission
 * @brief Stores info of each submission
 */
struct submission {
    int id = -1;
    int primary = -1;
    int secondary = -1;
};

/**
 * @struct parameters_
 * @brief Stores parameters info
 */
struct parameters_ {
    int minReviews = -1;
    int maxReviews = -1;
    int primaryRev = -1;
    int secondaryRev = -1;
    int primarySub = -1;
    int secondarySub = -1;
};

/**
 * @struct control_
 * @brief Stores control info
 */
struct control_ {
    int gen = -1;
    int risk = -1;
    std::string output;
};

class Parser {
  public:
    // Methods

    /**
     * @brief Initializes file variable with file_name param
     * @param file_name Name of the file to load
     */
    void load_file(const char* file_name);

    /**
     * @brief Parses the input file into objects
     */
    void parse_file();

    // Parameters
    const char* file = nullptr;
    std::vector<reviewer> reviewers;
    std::vector<submission> submissions;
    parameters_ parameters;
    control_ control;

  private:

    /**
     * @brief Converts string variable to integer
     * @param word String to convert
     * @return Int value that was converted
     */
    int read_value(char* word);

    /**
     * @brief Parses string line to a struct submission object
     * @param line String to parse
     * @param s submission object reference
     */
    void parse_line(char* line, submission& s);

    /**
     * @brief Parses string line to a struct reviewer object
     * @param line String to parse
     * @param r reviewer object reference
     */
    void parse_line(char* line, reviewer& r);

    /**
     * @brief Parses string line to a struct parameters_ object
     * @param line String to parse
     * @param p paramaters_ object reference
     * @param i Line number of parameters input
     */
    void parse_line(char* line, parameters_& p, int i);

    /**
     * @brief Parses string line to a struct control_ object
     * @param line String to parse
     * @param p control_ object reference
     * @param i Line number of parameters input
     */
    void parse_line(char* line, control_& p, int i);


    /**
     * @brief Parses input file to a vector of submissions
     * @param file File to parse
     * @param submissions Reference to vector of submissions
     */
    void parse(std::ifstream& file, std::vector<submission>& submissions);

    /**
     * @brief Parses input file to a vector of reviewers
     * @param file File to parse
     * @param submissions Reference to vector of reviewers
     */
    void parse(std::ifstream& file, std::vector<reviewer>& reviewers);

    /**
     * @brief Parses input file to a parameters_ object
     * @param file File to parse
     * @param parameters Reference to parameters_ object
     */
    void parse(std::ifstream& file, parameters_& parameters);

    /**
     * @brief Parses input file to a control_ object
     * @param file File to parse
     * @param parameters Reference to control_ object
     */
    void parse(std::ifstream& file, control_& control);

    /**
     * @brief Finds the header param string in input file
     * @param file File to search for string
     * @param header String to find in file
     * @return Ifstream of file in the place where the header param string was found
     */

    std::ifstream find_header(const char* file, const std::string& header);
};

#endif
