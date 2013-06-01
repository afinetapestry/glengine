#ifndef __EVENTABLE_HPP__
#define __EVENTABLE_HPP__

#ifdef WIN32
#include <SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

using namespace std;

class Eventable {
protected:
public:
	virtual void event(SDL_Event & e) {};
};

#endif

