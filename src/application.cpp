#include "application.h"
#include "state/mainMenu.h"

Application::Application() {
    state = new Main_menu();
    running = true;
}

Application::~Application() {
    if (state) delete state;
}

void Application::update() {
    state->act();
    State* next_state = state->transition();

    if (!next_state) {
        running = false;
        return;
    }

    if (next_state != state) {
        delete state;
        state = next_state;
    }
}

bool Application::is_running() {
    return running;
}
