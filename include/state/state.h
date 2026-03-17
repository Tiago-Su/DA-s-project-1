#ifndef GENERIC_STATE
#define GENERIC_STATE

#include <unordered_map>

class State {
  public:
    virtual ~State() = default;
    virtual void onEnter() = 0;
    virtual void act() = 0;
    virtual State* transition() = 0;

};

#endif
