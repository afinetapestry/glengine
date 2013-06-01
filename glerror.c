#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#ifdef WIN32
#include <GL/glew.h>
#elif __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL3/gl3.h>
#endif

int _glError(const char * file, int line) {
	GLenum err;
	int ret = 0;
	while ((err = glGetError()) != GL_NO_ERROR) {
		const char * str;
		switch (err) {
			case GL_INVALID_OPERATION: str = "GL_INVALID_OPERATION"; break;
			case GL_INVALID_ENUM: str = "GL_INVALID_ENUM"; break;
			case GL_INVALID_VALUE: str = "GL_INVALID_VALUE"; break;
			case GL_OUT_OF_MEMORY: str = "GL_OUT_OF_MEMORY"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: str = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		fprintf(stderr, "%s - %s:%d\n", str, file, line);
		ret = 1;
	}
	return ret;
}

#ifdef __cplusplus
}
#endif

