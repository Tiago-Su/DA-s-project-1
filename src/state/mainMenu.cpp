#include "state/mainMenu.h"
#include "state/explain.h"
#include <iostream>

Main_menu::Main_menu() {
    onEnter();
}

void Main_menu::onEnter() {}

void Main_menu::act() {
    std::cout << "\033c";
    std::cout << "=== DA's project ===" << std::endl;
    std::cout << std::endl;

    std::cout << "Current loaded file ---\n";
    std::cout << std::endl
              << "Options\n";

    std::cout << "1 - Explain tool\n";
    std::cout << "2 - Run\n";
    std::cout << "3 - Load datasets\n";
    std::cout << "4 - Credits\n";
    std::cout << "5 - Exit\n";
    std::cout << "Your answer: ";
}

State* Main_menu::transition() {
    int num;
    std::cin >> num;

    switch (num) {
        case 1:
            return new Explain();
            break;
        case 2:
            return new Explain();
            break;
        case 3:
            return new Explain();
            break;
        case 4:
            return new Explain();
            break;
        case 5:
			return nullptr;
            break;
    }

    return this;
}
