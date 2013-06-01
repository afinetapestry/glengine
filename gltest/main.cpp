#include <fstream>
#include <iostream>
#include <string>

#include <OpenGL/GL3.h>

#include <SDL2/SDL.h>

using namespace std;

void glError() {
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {throw exception();}
}

static string GetInfoLog(GLuint object, void (*glGet__iv)(GLuint, GLenum, GLint *), void (*glGet__InfoLog)(GLuint, GLsizei, GLsizei *, GLchar *)) {
	GLint length;
	string log;
	glGet__iv(object, GL_INFO_LOG_LENGTH, &length); glError();
	log.reserve(length);
	glGet__InfoLog(object, length, NULL, &log[0]); glError();
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
	GLuint shader = glCreateShader(type); glError();
	GLint status;
	glShaderSource(shader, 1, &str, &length); glError();
	glCompileShader(shader); glError();
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status); glError();
	if (!status) {
		string log = GetInfoLog(shader, glGetShaderiv, glGetShaderInfoLog);
		cerr << log << endl;
		throw exception();
	}
	glAttachShader(_program, shader);
}

void link(GLuint _program) {
	glLinkProgram(_program); glError();
	GLint status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status); glError();
	if (!status) {
		string log = GetInfoLog(_program, glGetProgramiv, glGetProgramInfoLog); glError();
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

	GLuint _program = glCreateProgram(); glError();
	addFile(_program, "simple.vert", GL_VERTEX_SHADER);
	addFile(_program, "simple.frag", GL_FRAGMENT_SHADER);
	link(_program);

	GLuint _vao = 0;
	GLuint _vbo = 0;

	glGenVertexArrays(1, &_vao); glError();
	glBindVertexArray(_vao); glError();

	// make and bind the VBO
	glGenBuffers(1, &_vbo); glError();
	glBindBuffer(GL_ARRAY_BUFFER, _vbo); glError();

	// Put the three triangle verticies into the VBO
	GLfloat vertexData[] = {
		//  X     Y     Z
		 0.0f, 0.8f, 0.0f,
		-0.8f,-0.8f, 0.0f,
		 0.8f,-0.8f, 0.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); glError();

	// connect the xyz to the "vert" attribute of the vertex shader
	glEnableVertexAttribArray(glGetAttribLocation(_program, "vert")); glError();
	glVertexAttribPointer(glGetAttribLocation(_program, "vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL); glError();

	// unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0); glError();
	glBindVertexArray(0); glError();

	glViewport(0, 0, 1024, 600); glError();

	bool _running = true;
	while (_running) {
		/*const char * err;
		if (*(err = SDL_GetError()) != '\0') {
			cerr << err;
			return EXIT_FAILURE;
		}*/
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

		glClearColor(1, 0, 0, 1); glError();
		glClear(GL_COLOR_BUFFER_BIT); glError();
    
		glUseProgram(_program); glError();
			
		glBindVertexArray(_vao); glError();
		
		glDrawArrays(GL_TRIANGLES, 0, 3); glError();
		
		glBindVertexArray(0); glError();
		
		glUseProgram(0); glError();

		SDL_GL_SwapWindow(_window);
	}

	SDL_GL_DeleteContext(_context); glError();
	SDL_DestroyWindow(_window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
