#ifndef __UPDATEABLE_HPP__
#define __UPDATEABLE_HPP__

#include <SDL2/SDL.h>

using namespace std;

class Updateable {
public:
	virtual void update(Uint32 delta) {};
};

#endif

