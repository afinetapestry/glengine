#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <map>
#include <stdexcept>

#include "glexception.hpp"

using namespace std;

class Texture {
	public:
		GLuint _texture;
		GLenum _target;
		map<GLenum, GLint> _paramsi;

		Texture() : _texture(0),
					_target(GL_TEXTURE_2D),
					_paramsi(const map<GLenum, GLint> &)boost::assign::map_list_of(GL_TEXTURE_MIN_FILTER, GL_NEAREST)(GL_TEXTURE_MAG_FILTER, GL_NEAREST)(GL_TEXTURE_WRAP_S, GL_REPEAT)(GL_TEXTURE_WRAP_T, GL_REPEAT)) {
			glGenTextures(1, &_texture);
			_glException();
		}
		~Texture() {
			glDeleteTexture(_texture);
			_glException();
		}

		void loadImage() {
			glBindTexture(_target, _texture);
			_glException();
			setParameters();
			//glTextImage2D(_target, 0, internalFormat, width, height, 0, format, data, pointer);
			_glException();
			glBindTexture(0);
			_glException();
		}

		void setParameters() {
			for (map<GLenum, GLint>::iterator i = _parami.begin(); i != _parami.end(); ++i) {
				glTextParameteri(_target, i->first, i->second);
				_glException();
			}
		}

		void bind() {
			glBindTexutre(_target, _texture);
			_glException();
		}

		void unbind() {
			glBindTexture(_target, 0);
			_glException();
		}
};

#endif

