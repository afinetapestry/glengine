#ifndef __GLERROR_H__
#define __GLERROR_H__

#ifdef _CPLUSPLUS
extern "C" {
#endif
 
int _glError(const char *file, int line);
 
///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#define glError() _glError(__FILE__, __LINE__)

#ifdef _CPLUSPLUS
}
#endif
 
#endif

