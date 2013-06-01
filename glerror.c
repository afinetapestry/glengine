#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "gl.h"
#include "glerror.h"

const char * __glError(const char * file, const int line) {
	switch (glGetError()) {
		case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION"; break;
		case GL_INVALID_ENUM: return "GL_INVALID_ENUM"; break;
		case GL_INVALID_VALUE: return "GL_INVALID_VALUE"; break;
		case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
		case GL_NO_ERROR: return 0; break;
		default: return "UNKOWN_ERROR"; break;
	}
}

#ifdef __cplusplus
}
#endif