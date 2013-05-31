#include <string>

#include "engine.hpp"
#include "program.hpp"

using namespace std;

class Cube : public Renderable {
	public:
		Cube(Program & program) : Renderable(program) {
			glBindVertexArray(_vao);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			GLfloat data[] = {
				//  X     Y     Z
				0.0f, 0.8f, 0.0f,
				-0.8f, -0.8f, 0.0f,
				0.8f, -0.8f, 0.0f,
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
			glEnableVertexAttribArray(_program.attrib("vert"));
			glVertexAttribPointer(_program.attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
			_first = 0;
			_count = 3;
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
};

int main(int argc, char *argv[]) {
	Engine engine = Engine::GetInstance();
	engine.init();
	engine._targetFPS = 60;

	Program program("simple.vert", "simple.frag");

	Cube cube(program);
	engine.addRenderHandler(&cube);

	// Remove
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	engine.run();

	return EXIT_SUCCESS;
}

