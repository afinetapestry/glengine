#include <string>

#include "engine.hpp"
#include "gl.h"
#include "glexception.hpp"
#include "program.hpp"

#ifdef WIN32
#undef main
#endif

using namespace std;

class Cube : public Renderable {
	public:
		Cube(Program & program) : Renderable(program) {
			glBindVertexArray(_vao);
			_glException();
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			_glException();
			GLfloat data[] = {
				//  X     Y     Z
				0.0f, 0.8f, 0.0f,
				-0.8f, -0.8f, 0.0f,
				0.8f, -0.8f, 0.0f,
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
			_glException();
			glEnableVertexAttribArray(_program.attrib("vert"));
			_glException();
			glVertexAttribPointer(_program.attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
			_glException();
			_first = 0;
			_count = 3;
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			_glException();
			glBindVertexArray(0);
			_glException();
		}
};

int main(int argc, char *argv[]) {

	Engine engine = Engine::GetInstance();
	engine.init();
	engine._targetFPS = 60;

	Program program("simple.vert", "simple.frag");

	Cube cube(program);
	engine.addRenderHandler(&cube);

	engine.run();

	return EXIT_SUCCESS;
}

