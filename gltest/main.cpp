#include <fstream>
#include <iostream>
#include <string>

#include <OpenGL/GL.h>

#include <SDL2/SDL.h>

using namespace std;

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

void addFile(GLuint _program, const string & filename, GLenum type) {
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

void link(GLuint _program) {
	glLinkProgram(_program);
	GLint status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if (!status) {
		string log = GetInfoLog(_program, glGetProgramiv, glGetProgramInfoLog);
		cerr << log << endl;
		throw exception();
	}
}

int main(int argc, char *argv[]) {
	SDL_Window * _window;
	SDL_GLContext _context;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window = SDL_CreateWindow("GLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	_context = SDL_GL_CreateContext(_window);

	GLuint _program = glCreateProgram();
	addFile(_program, "simple.vert", GL_VERTEX_SHADER);
	addFile(_program, "simple.frag", GL_FRAGMENT_SHADER);
	link(_program);
	glUseProgram(_program);

	bool _running = true;
	while (_running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) { // While there are events waiting
			switch (event.type) {
				case SDL_QUIT: {_running = false;} break; // Handle quit, don't remove this thinking OS X will do it.
				case SDL_KEYDOWN: {
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE: {_running = false;} break;
					}
				} break;
			}
		}
	}

	return EXIT_SUCCESS;
}
