#include <stdio.h>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <iostream>



struct reviewer
{
    unsigned int id;
    int primary;
    int secondary;
};

struct submission
{
    unsigned int id;
    int primary;
    int secondary;
};

std::vector<reviewer> reviewer_parser(std::ifstream & fd){
    
    
    std::string line;
    
    std::vector<reviewer> reviewers;
    
    std::getline(fd, line);
    std::getline(fd, line);

    while (line[0] != '#')
    {
        reviewer reviewer;
        
        char * input;
        
        char buffer[100];
        std::strcpy(buffer, line.c_str());
        
        const char delim[2] = ",";
        input = std::strtok(buffer, delim);
        
        reviewer.id = atoi(input);
        int value;

        for(int i = 0; i< 2; i++){
            std::strtok(NULL, delim);
        }
        input = std::strtok(NULL, delim);
        value = atoi(input);
        reviewer.primary = value;
        
        
        input = std::strtok(NULL, delim);
        if (input == nullptr) {
            value = -1;
        } 
        else {
            value = atoi(input);
        }
        
        reviewer.secondary = value;
        
        reviewers.push_back(reviewer);

        std::getline(fd, line);
        
    }
    std::cout <<reviewers.size() << std::endl;
    return reviewers;
}

std::vector<submission> submission_parser(std::ifstream & fd){
    
    
    std::string line;
    
    std::vector<submission> submissions;
    
    std::getline(fd, line);
    std::getline(fd, line);

    while (line[0] != '#')
    {
        submission submission;
        
        char * input;
        
        char buffer[100];
        std::strcpy(buffer, line.c_str());
        
        const char delim[2] = ",";
        input = std::strtok(buffer, delim);
        
        submission.id = atoi(input);
        int value;

        for(int i = 0; i< 3; i++){
            std::strtok(NULL, delim);
        }
        input = std::strtok(NULL, delim);
        value = atoi(input);
        submission.primary = value;
        
        
        input = std::strtok(NULL, delim);
        if (input == nullptr) {
            value = -1;
        } 
        else {
            value = atoi(input);
        }
        
        submission.secondary = value;
        
        submissions.push_back(submission);

        std::getline(fd, line);
        
    }
    return submissions;
}


int main() {

    std::ifstream in("data1.csv");

    std::vector<submission> submissions;
    std::vector<reviewer> reviewers;

    std::string line;
    std::getline(in, line);

    submissions = submission_parser(in);

    for (submission sub : submissions){
        std::cout << sub.id << ' ' << sub.primary << ' ' << sub.secondary << std::endl;
    }

    reviewers = reviewer_parser(in);

    for (reviewer rev : reviewers){
        std::cout << rev.id << ' ' << rev.primary << ' ' << rev.secondary << std::endl;
    }

    return 0;
}