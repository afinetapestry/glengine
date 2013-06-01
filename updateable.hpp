#ifndef __UPDATEABLE_HPP__
#define __UPDATEABLE_HPP__

#ifdef WIN32
#include <SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

using namespace std;

class Updateable {
public:
	virtual void update(Uint32 delta) {};
};

#endif

