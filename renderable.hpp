#ifndef __RENDERABLE_HPP__
#define __RENDERABLE_HPP__

#include <vector>

#include "program.hpp"

#include "gl.h"
#include "glexception.hpp"

using namespace std;

class Renderable {
public:
	GLuint _vao;
	GLuint _vbo;
	GLenum _mode;
	GLint _first;
	GLsizei _count;
	vector<GLfloat> _data;
	Program & _program;

	Renderable(Program & program) :	_vao(0),
									_vbo(0),
									_mode(GL_TRIANGLES),
									_first(0),
									_count(0),
									_program(program) {
		glGenVertexArrays(1, &_vao);
		_glException();
		glGenBuffers(1, &_vbo);
		_glException();
	}

	virtual vector<GLfloat> & submit() {
		return _data;
	}

	virtual void render() {
		_program.use();
		glBindVertexArray(_vao);
		_glException();
		glDrawArrays(_mode, _first, _count);
		_glException();
		glBindVertexArray(0);
		_glException();
		glUseProgram(0);
		_glException();
	}
};

#endif

