#ifndef __RENDERABLE_HPP__
#define __RENDERABLE_HPP__

#include <vector>

#include <OpenGL/GL.h>

#include "program.hpp"

using namespace std;

#ifdef __APPLE__
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#endif

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
		glGenBuffers(1, &_vbo);
	}

	virtual vector<GLfloat> & submit() {
		return _data;
	}

	virtual void render() {
		_program.use();
		glBindVertexArray(_vao);
		glDrawArrays(_mode, _first, _count);
		glBindVertexArray(0);
		glUseProgram(0);
	}
};

#endif

