#ifndef MAIN_MENU
#define MAIN_MENU

#include "state.h"

class Main_menu : public State {
  public:
	Main_menu();	
	void onEnter() override;
	void act() override;
	State* transition() override;
};

#endif
