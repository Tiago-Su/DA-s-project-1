//
// Created by state_machine on 3/19/26.
//

#ifndef PROJECT_TUI_H
#define PROJECT_TUI_H
#include <string>
#include "tool.h"

class Tui {
public:
    bool running = true;
    void menuHandler();
    void displayMenu();
    int getOption();
    void optionHandler(int option);
    void displayDescription();
    void selectDataSet();
    bool isDataSetSelected();
    void run();
    Tool tool;
    void displayRunMenu();
    void runOptionHandler(int option);
    int getRunOption();
    void runHandler();
    void displayCredits();
    void displayPrintMenu();
    void printOptionHandler(int option);
    int getPrintOption();
    void printHandler();

   std::string dataSetPath;
    bool isRunning;
};


#endif //PROJECT_TUI_H