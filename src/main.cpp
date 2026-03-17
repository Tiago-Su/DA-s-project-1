#include "application.h"

int main() {
	Application app = Application();
	while (app.is_running()) {
		app.update();
	}

	return 0;
}
