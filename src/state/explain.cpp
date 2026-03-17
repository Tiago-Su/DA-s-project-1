#include "state/explain.h"
#include "state/mainMenu.h"
#include <iostream>

Explain::Explain() {
	onEnter();
}

void Explain::onEnter() {
	std::cout << "\033c";
	std::cout << "This is a project made for ...\n";
}

void Explain::act() {
	std::cout << std::endl;
	std::cout << "1 - Go back to main menu\n";
	std::cout << "Your answer: ";
}

State* Explain::transition() {
	int num;
	std::cin >> num;
	if (num == 1) {
		return new Main_menu();
	}

	return this;
}
