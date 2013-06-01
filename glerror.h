#ifndef __GLERROR_H__
#define __GLERROR_H__

#ifdef __cplusplus
extern "C" {
#endif
 
const char * __glError(const char *, const int);
 
///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#define _glError() __glError(__FILE__, __LINE__)

#ifdef __cplusplus
}
#endif
 
#endif

