#ifndef __EVENTABLE_HPP__
#define __EVENTABLE_HPP__

#include <SDL2/SDL.h>

using namespace std;

class Eventable {
protected:
public:
	virtual void event(SDL_Event & e) {};
};

#endif

