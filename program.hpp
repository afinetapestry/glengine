#ifndef __PROGRAM_HPP__
#define __PROGRAM_HPP__

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <OpenGL/GL.h>

using namespace std;

class Program {
	public:
		bool _linked;
		GLuint _program;
		map<string, GLint> _uniforms;
		map<string, GLint> _attrib;

		Program() :	_linked(false),
					_program(0) {
			_program = glCreateProgram();
		}
		Program(const string & vert, const string & frag) {
			Program();
			addFile(vert, GL_VERTEX_SHADER);
			addFile(frag, GL_FRAGMENT_SHADER);
			link();
		}
		~Program() {
			if (_program != 0) {glDeleteProgram(_program); _program = 0;}
		}

		void addFile(const string & filename, GLenum type) {
			string source = LoadFile(filename);
			const char * str = source.c_str();
			int length = source.length();
			GLuint shader = glCreateShader(type);
			GLint status;
			glShaderSource(shader, 1, &str, &length);
			glCompileShader(shader);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
			if (!status) {
				string log = GetInfoLog(shader, glGetShaderiv, glGetShaderInfoLog);
				cerr << log << endl;
				throw exception();
			}
			glAttachShader(_program, shader);
		}

		void link() {
			glLinkProgram(_program);
			GLint status;
			glGetProgramiv(_program, GL_LINK_STATUS, &status);
			if (!status) {
				string log = GetInfoLog(_program, glGetProgramiv, glGetProgramInfoLog);
				cerr << log << endl;
				throw exception();
			}
			_linked = true;
		}

		void use() {
			if (!_linked) {link();}
			glUseProgram(_program);
		}

		GLint uniform(const string & name) {
			map<string, GLint>::iterator i;
			GLint location;
			if ((i = _uniforms.find(name)) == _uniforms.end()) {
				location = _uniforms[name] = glGetUniformLocation(_program, name.c_str());
			} else {
				location = _uniforms[name];
			}
			return location;
		}

		GLint attrib(const string & name) {
			map<string, GLint>::iterator i;
			GLint location;
			if ((i = _attrib.find(name)) == _attrib.end()) {
				location = _attrib[name] = glGetUniformLocation(_program, name.c_str());
			} else {
				location = _attrib[name];
			}
			return location;
		}

		void uniform1f(const string & name, float v0) {
			GLint location = uniform(name);
			glUniform1f(location, v0);
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

		static string GetInfoLog(GLuint object, void (*glGet__iv)(GLuint, GLenum, GLint *), void (*glGet__InfoLog)(GLuint, GLsizei, GLsizei *, GLchar *)) {
			GLint length;
			string log;
			glGet__iv(object, GL_INFO_LOG_LENGTH, &length);
			log.reserve(length);
			glGet__InfoLog(object, length, NULL, &log[0]);
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

