#ifndef __PROGRAM_HPP__
#define __PROGRAM_HPP__

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "gl.h"
#include "glexception.hpp"

using namespace std;

#ifndef WIN32
#define __stdcall
#endif

class Program {
	public:
		bool _linked;
		GLuint _program;
		map<string, GLint> _uniforms;
		map<string, GLint> _attrib;

		Program() :	_linked(false),
					_program(0) {
			init();
		}
		Program(const string & vert, const string & frag) :	_linked(false),
															_program(0) {
			init();
			addFile(vert, GL_VERTEX_SHADER);
			addFile(frag, GL_FRAGMENT_SHADER);
			link();
		}
		~Program() {
			if (_program != 0) {
				glDeleteProgram(_program);
				_glException();
				_program = 0;
			}
		}

		void init() {
			_program = glCreateProgram();
			_glException();
		}

		void addFile(const string & filename, GLenum type) {
			string source = LoadFile(filename);
			const char * str = source.c_str();
			int length = source.length();
			GLuint shader = glCreateShader(type);
			_glException();
			GLint status;
			glShaderSource(shader, 1, &str, &length);
			_glException();
			glCompileShader(shader);
			_glException();
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
			_glException();
			if (!status) {
				string log = GetInfoLog(shader, *glGetShaderiv, *glGetShaderInfoLog);
				cerr << log << endl;
				throw exception();
			}
			glAttachShader(_program, shader);
			_glException();
		}

		void link() {
			glLinkProgram(_program);
			_glException();
			GLint status;
			glGetProgramiv(_program, GL_LINK_STATUS, &status);
			_glException();
			if (!status) {
				string log = GetInfoLog(_program, *glGetProgramiv, *glGetProgramInfoLog);
				cerr << log << endl;
				throw exception();
			}
			_linked = true;
		}

		void use() {
			if (!_linked) {link();}
			glUseProgram(_program);
			_glException();
		}

		GLint uniform(const string & name) {
			map<string, GLint>::iterator i;
			GLint location;
			if ((i = _uniforms.find(name)) == _uniforms.end()) {
				location = _uniforms[name] = glGetUniformLocation(_program, name.c_str());
				_glException();
			} else {
				location = _uniforms[name];
			}
			return location;
		}

		GLint attrib(const string & name) {
			map<string, GLint>::iterator i;
			GLint location;
			if ((i = _attrib.find(name)) == _attrib.end()) {
				location = _attrib[name] = glGetAttribLocation(_program, name.c_str());
				_glException();
			} else {
				location = _attrib[name];
			}
			return location;
		}

		void uniform1f(const string & name, float v0) {
			GLint location = uniform(name);
			glUniform1f(location, v0);
			_glException();
		}

		/*void glUniform2f(	GLint  	location,
		  GLfloat  	v0,
		  GLfloat  	v1);
		  void glUniform3f(	GLint  	location,
		  GLfloat  	v0,
		  GLfloat  	v1,
		  GLfloat  	v2);
		  void glUniform4f(	GLint  	location,
		  GLfloat  	v0,
		  GLfloat  	v1,
		  GLfloat  	v2,
		  GLfloat  	v3);
		  void glUniform1i(GLint location, GLint v0);

		  void glUniform2i(	GLint  	location,
		  GLint  	v0,
		  GLint  	v1);
		  void glUniform3i(	GLint  	location,
		  GLint  	v0,
		  GLint  	v1,
		  GLint  	v2);
		  void glUniform4i(	GLint  	location,
		  GLint  	v0,
		  GLint  	v1,
		  GLint  	v2,
		  GLint  	v3);
		  void glUniform1ui(GLint location, GLuint v0);

		  void glUniform2ui(	GLint  	location,
		  GLuint  	v0,
		  GLuint  	v1);
		  void glUniform3ui(	GLint  	location,
		  GLuint  	v0,
		  GLuint  	v1,
		  GLuint  	v2);
		  void glUniform4ui(	GLint  	location,
		  GLuint  	v0,
		  GLuint  	v1,
		  GLuint  	v2,
		  GLuint  	v3);*/

		static string GetInfoLog(GLuint object, void (_GL_CALL *glGet__iv)(GLuint, GLenum, GLint *), void (_GL_CALL *glGet__InfoLog)(GLuint, GLsizei, GLsizei *, GLchar *)) {
			GLint length;
			string log;
			glGet__iv(object, GL_INFO_LOG_LENGTH, &length);
			_glException();
			log.reserve(length);
			glGet__InfoLog(object, length, NULL, &log[0]);
			_glException();
			return log;
		}

		static string LoadFile(const string & filename) {
			ifstream file;
			file.exceptions(std::ifstream::failbit);
			file.open(filename.c_str());
			string text(istreambuf_iterator<char>(file), (istreambuf_iterator<char>()));
			return text;
		}
};

#endif

