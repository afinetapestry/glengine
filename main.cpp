#include <string>

#ifdef WIN32
#include <GL/glew.h>
#elif __APPLE__
#include <OpenGL/glew.h>
#else
#include <GL3/gl3.h>
#endif



#include "engine.hpp"
#include "program.hpp"

#undef main

using namespace std;

class Cube : public Renderable {
	public:
		Cube(Program & program) : Renderable(program) {
			glBindVertexArray(_vao);
			if (glError()) {throw exception();}
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			if (glError()) {throw exception();}
			GLfloat data[] = {
				//  X     Y     Z
				0.0f, 0.8f, 0.0f,
				-0.8f, -0.8f, 0.0f,
				0.8f, -0.8f, 0.0f,
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
			if (glError()) {throw exception();}
			glEnableVertexAttribArray(_program.attrib("vert"));
			if (glError()) {throw exception();}
			glVertexAttribPointer(_program.attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
			if (glError()) {throw exception();}
			_first = 0;
			_count = 3;
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			if (glError()) {throw exception();}
			glBindVertexArray(0);
			if (glError()) {throw exception();}
		}
};

int __cdecl main(int argc, char *argv[]) {
	Engine engine = Engine::GetInstance();
	engine.init();
	engine._targetFPS = 60;
	
	Program program;
	program.addFile("simple.vert", GL_VERTEX_SHADER);
	program.addFile("simple.frag", GL_FRAGMENT_SHADER);
	program.link();

	Cube cube(program);
	engine.addRenderHandler(&cube);

	engine.run();

	return EXIT_SUCCESS;
}

