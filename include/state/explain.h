#ifndef EXPLAIN
#define EXPLAIN

#include "state/state.h"

class Explain : public State {
  public:
	Explain();	
	void onEnter() override;
	void act() override;
	State* transition() override;
};

#endif
