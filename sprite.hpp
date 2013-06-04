#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__

#include "renderable.hpp"
#include "texture.hpp"

class Sprite : Renderable {
	public:
		Texture & _texture;

		Sprite(Program & program, Texture & texture) :	Renderable(program),
														Texture() {
		}
};

#endif

