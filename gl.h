#include <GL/glew.h>

#ifdef WIN32
#include <Windows.h>
#define _GL_CALL APIENTRY
#elif __APPLE__
#include <OpenGL/gl3.h>
#define _GL_CALL __cdecl
#else
#include <GL3/gl3.h>
#define _GL_CALL __cdecl
#endif

