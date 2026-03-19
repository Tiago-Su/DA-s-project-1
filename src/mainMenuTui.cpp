//
// Created by state_machine on 3/19/26.
//
#include <iostream>
#include "../include/mainMenuTui.h"
#include "../include/tool.h"
#include <fstream>
#include <random>

void Tui::menuHandler() {
    isRunning = true;
    while (isRunning) {
        displayMenu();
        int option = getOption();
        optionHandler(option);
    }
}

void Tui::displayMenu() {
    std::cout << std::endl;
    std::cout << "Please enter the option number. Use 5 as a command to retrocede back to Main Menu"<<std::endl<<std::endl;
    std::cout<<"1: Description"<<std::endl;
    std::cout<<"2: Select Dataset"<<std::endl;
    std::cout<<"3: Run"<<std::endl;
    std::cout<<"4: Credits"<<std::endl;
    std::cout << "5: Exit"<<std::endl;
}

int Tui::getOption() {
    int option;
    while (true) {
        std::cout << std::endl<<"Option:" ;
        std::cin >> option;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout <<std::endl<< "Invalid input. Please enter a number.";
        }
        else if (option<1 || option>5) {
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a valid option.";
        }
        else {
            std::cin.ignore(1000, '\n');
            isRunning=false;
            return option;
        }
    }
}

void Tui::optionHandler(int option) {
    switch (option) {
        case 1: displayDescription();
            break;
        case 2: selectDataSet();
            break;
        case 3: run();
            break;
        case 4: displayCredits();
            break;
        case 5: exit(0);
            break;
    }
}
bool verifyFileExistence(const std::string path) {
    std::ifstream file(path);
    return file.good();
}


void Tui::selectDataSet() {
    while (true) {
        std::cout << "Enter dataset path:";
        std::string path;
        std::getline(std::cin, path);
        if (path=="5") {
            isRunning = true;
            return;
        }
        if (verifyFileExistence(path)) {
            dataSetPath = path;
            std::cout << std::endl<<"Dataset selected." << std::endl;
            isRunning = true;
            return;
        }
        else {
            dataSetPath.clear();
            std::cout << std::endl << "Invalid path. Please enter a valid dataset path.";
            std::cout << std::endl;
        }
    }
}

bool Tui::isDataSetSelected() {
    if (dataSetPath.empty()) {
        return false;
    }
    return true;
}

void Tui::run() {
if (isDataSetSelected()) {
    Tool tool;
    tool.setup(const_cast<char*>(dataSetPath.c_str()));
    tool.get_max_flow();
    tool.print_output();
}
    else {
    std::cout << "No selection of DataSet. Please go over to the 'Select DataSet' option (2) and enter a valid DataSet";
    }
    int option;
    std::cin >> option;
    if (option == 5) {
        isRunning = true;
    }
}

void Tui::displayCredits() {
    std::cout << std::endl << "Credits selected." << std::endl;
}
void Tui::displayDescription() {
    std::cout << "Description"<<std::endl<<std::endl;
    while (true) {
        int option;
        std::cin >> option;
        if (option == 5) {
            break;
        }
        std::cout << std::endl<<"Invalid command. Use 5 to retrocede"<<std::endl;
    }

}