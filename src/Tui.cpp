#include "Tui.h"
#include "tool.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <filesystem>

void Tui::menuHandler() {
    isRunning = true;
	std::filesystem::create_directory("./program_output");

    while (isRunning) {
        displayMenu();
        int option = getOption();
        optionHandler(option);
    }
}
/**
 * @brief Clears the terminal.
 **/
void clear() {
    std::cout << "\033[2J\033[1;1H";
}

void Tui::displayMenu() {
    clear();
    std::cout << "Please enter the option number." << std::endl << std::endl;
	std::cout << "Selected dataset: ";
	if (dataSetPath.empty()) std::cout << "None\n\n";
	else std::cout << dataSetPath << std::endl << std::endl;;

    std::cout << "1: Description" << std::endl;
    std::cout << "2: Select Dataset" << std::endl;
    std::cout << "3: Run" << std::endl;
    std::cout << "4: Credits" << std::endl;
    std::cout << "5: Exit" << std::endl;
}

int Tui::getOption() {
    int option;
    while (true) {
        std::cout << std::endl << "Option:";
        std::cin >> option;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << std::endl << "Invalid input. Please enter a number.";
        } else if (option < 1 || option > 5) {
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a valid option.";
        } else {
            std::cin.ignore(1000, '\n');
            return option;
        }
    }
}

void Tui::optionHandler(int option) {
    switch (option) {
        case 1:
            displayDescription();
            break;
        case 2:
            selectDataSet();
            break;
        case 3:
            run();
            break;
        case 4:
            displayCredits();
            break;
        case 5:
            exit(0);
            break;
    }
}
/**
 * @brief Verifies if a given file exists.
 * @param string : path of file
 * @return: bool: true if file exists, false otherwise.
 **/
bool verifyFileExistence(const std::string path) {
    std::ifstream file(path);
    return file.good();
}

void Tui::selectDataSet() {
    clear();
    while (true) {
        std::cout << "Enter dataset path:";
        std::string path;
        std::getline(std::cin, path);
        if (path == "5") {
            isRunning = true;
            return;
        }

        if (verifyFileExistence(path)) {
            dataSetPath = path;
            std::cout << std::endl << "Dataset selected." << std::endl;
            isRunning = true;
            return;
        } else {
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

void Tui::displayRunMenu() {
    clear();
    std::cout << "1. Print" << std::endl;
    std::cout << "2. Save to File" << std::endl;
    std::cout << "3. Risk Analysis" << std::endl;
	std::cout << "5. Go back to main menu\n";
}

void Tui::runHandler() {
    while (true) {
        displayRunMenu();
        int option = getRunOption();
        if (option == 5) return;
        runOptionHandler(option);
    }
}
/**
* @brief Pauses execution until the user enters the exit command.
* @details
* Repeatedly prompts the user to enter `5` and blocks execution until
* the correct value is provided.
**/
void onHold() {
    while (true) {
        std::cout << std::endl;
        std::cout << "Enter 5 to retrocede: ";
        int option;
        std::cin >> option;

        if (option == 5) break;
        std::cout << "Invalid input." << std::endl;
    }
}
void Tui::runOptionHandler(int option) {
    switch (option) {
        case 1:
            printHandler();
            break;
        case 2:
			tool.save_to_file();
			onHold();
            break;
        case 3:
            tool.risk_analysis();
            tool.print_risk_analysis();
            onHold();
            break;
    }
}

int Tui::getRunOption() {
    int option;
    while (true) {
        std::cout << std::endl << "Option:";
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << std::endl << "Invalid input. Please enter a number.";

        } else if (option == 5) {
            return 5;

        } else if (option < 1 || (option > 3)) {
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a valid option.";

        } else {
            std::cin.ignore(1000, '\n');
            isRunning = false;
            return option;
        }
    }
}

void Tui::run() {
    clear();
    if (isDataSetSelected()) {
        tool.setup(const_cast<char*>(dataSetPath.c_str()));
        tool.get_max_flow();
        tool.get_missing_output();

        runHandler();
    } else {
        std::cout << "No selection of DataSet. Please go over to the 'Select DataSet' option (2) and enter a valid DataSet\n";
		onHold();
    }
}

void Tui::displayCredits() {
    clear();
    std::cout << std::endl << "Credits:" << std::endl;
	std::cout << "This program was made by:\n";
	std::cout << "- Francisca Baldaia da Silveira\n";
	std::cout << "- Tiago Alexandre Rodrigues Botelho\n";
	std::cout << "- Tiago Su\n";
	onHold();
}

void Tui::displayDescription() {
    clear();
    std::cout << "Description:" << std::endl << std::endl;
	std::cout << "This project was made for the subject \"Desenho de Algoritmos\" and the objective of this program is the following:\n";
	std::cout << "Given a set of articles with domains and a set of reviewers with expertise in certain domains, the goal is to find the best or one of the best distributions\nknowing that reviewers can only review a maximum amount of articles and an article needs at least a minimum amount of reviewers.\nIf not all articles can be assigned reviewers, the program prints the unassigned articles.\n";
	std::cout << "Besides the main algorithm, there is a feature to find critical reviewers, that is: the reviewers that, if failing to do their assignment,\nwill cause a failure.\n\n";
	onHold();
}

void Tui::displayPrintMenu() {
    clear();
    std::cout << "1. Print Settings" << std::endl;
    std::cout << "2. Print Submissions" << std::endl;
    std::cout << "3. Print Reviewers" << std::endl;
    std::cout << "4. Print Results" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

void Tui::printOptionHandler(int option) {
    clear();

    switch (option) {
        case 1:
            tool.printParametersControl();
            break;
        case 2:
            tool.printSubmissions();
            break;
        case 3:
            tool.printReviewers();
            break;
        case 4:
            std::cout << "Results\n";
            tool.print_output();
            break;
    }
}

void Tui::printHandler() {
    while (true) {
        displayPrintMenu();
        int option = getOption();
        if (option == 5) {
            return;
        }

        printOptionHandler(option);
        onHold();
    }
}
