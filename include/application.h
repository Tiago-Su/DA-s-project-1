#ifndef APPLICATION
#define APPLICATION

#include "state/state.h"

class Application {
  public:
	Application();
	~Application();

	void update();
	bool is_running();

  private:
	State* state;	
	bool running;
};

#endif
