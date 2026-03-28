//
// Created by state_machine on 3/19/26.
//

#ifndef PROJECT_TUI_H
#define PROJECT_TUI_H
#include <string>
#include "tool.h"

class Tui {
public:
    Tool tool;
    /**
     * @brief Control flow of the main menu
     * @details Uses isRunning variable to check active state of the main menu and, while true, continuously loops over functions that are responsible for menu display, option getter and option handler to respond adequately to input.
     **/
    void menuHandler();
    /**
    * @brief Displays main menu
    * @details Clears the terminal and writes main menu options to standard output.
    **/
    void displayMenu();
    /**
* @brief Retrieves and validates a menu option from standard input, returning said option if validated.
* @details Prompts the user to select an option until a valid integer within the acceptance range [1,5] is provided to standard input, displaying error messages upon invalid input.
* @return int Selected option
**/
    int getOption();
    /**
 * @brief Dispatches main menu option to corresponding "handler" method.
 * @details Maps the provided menu option to its corresponding "handler", delegating execution to that method responsible for that operation.
 * @param int Valid main menu option in range [1,5]
 **/
    void optionHandler(int option);
    /**
* @brief Displays description, awaiting user exit command.
* @details Clears the terminal and displays the description of the project, then entering a blocking input loop that waits until the user enters the command `5` to return to the previous menu.
**/
    void displayDescription();
    /**
* @brief Prompts the user for a dataset path and stores it upon successful validation. Clears previous path, upon any user input, even if invalid.
* @details  Clears the terminal and repeatedly prompts the user to enter a valid dataset file path, whose validation is verified through the calling of verifyFileExistence(). Upon validation, path is stored in public class parameter. If the input is `"5"`, the operation is cancelled and control returns to the menu. A invalid paths result in an error message and a repeated prompt. Clears previous path, upon any user input, even if invalid; if invalid, path is simply cleared and if valid it is replaced.
**/
    void selectDataSet();
    /**
* @brief Checks whether a dataSet is currently selected.
* @return bool : true if a dataset path is currently stored; returns false otherwise.
**/
    bool isDataSetSelected();
    /**
* @brief Executes the workflow for the selected dataset, generating the submission assignments, and making the results available for selection through the "post-run" menu.
* @details Sets up and adapts the selected dataSet data and runs the adapted Maximal Bipartite Matching algorithm, generating the submission assignments for the dataset, if possible (if a possible solution exists). Then, calls runHandler() which handles the post-run menu workflow, a menu for viewing and printing the results.
**/
    void run();
    /**
* @brief Displays the post-run menu options.
* @details Clears the terminal and prints the available actions after the dataSet workflow has been executed.
**/
    void displayRunMenu();
    /**
  * @brief Dispatches post-run menu option to corresponding "handler" method.
  * @details Maps the provided option to its corresponding execution methods.
  * @param int: the selected option
  **/
    void runOptionHandler(int option);
    /**
* @brief Retrieves and validates a run menu option.
* @details Prompts the user for input and repeats until a valid option is entered.
* @return int: selected menu option for the run menu
    **/

    int getRunOption();
    /**
* @brief Controls the post-run menu loop.
* @details Repeatedly displays the run menu, retrieves the user's selected option,
* and dispatches it to runOptionHandler. The loop continues until the
* user selects the exit option (5), returning to the main menu.
**/
    void runHandler();
    /**
    * @brief Displays the program credits.
    * @details Clears the terminal and prints the names of the contributors.**/
    void displayCredits();
    /**
  * @brief Displays the options of print menu.
  * @details Clears the terminal and prints the options.**/
    void displayPrintMenu();
    /**
  * @brief Dispatches print menu option to corresponding "handler" method.
  * @details Maps the provided option to its corresponding execution methods.
  * @param int: the selected option
  **/
    void printOptionHandler(int option);
    /**
* @brief Controls the print menu loop.
* @details Repeatedly displays the print menu, retrieves the user's selected option,
* and dispatches it to printOptionHandler. The loop continues until the
* user selects the exit option (5), returning to the run menu.
**/
    void printHandler();

   std::string dataSetPath;
    bool isRunning;
};


#endif //PROJECT_TUI_H