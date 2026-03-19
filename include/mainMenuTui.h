//
// Created by state_machine on 3/19/26.
//

#ifndef PROJECT_TUI_H
#define PROJECT_TUI_H
#include <string>


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
    void displayCredits();

   std::string dataSetPath;
    bool isRunning;
};


#endif //PROJECT_TUI_H