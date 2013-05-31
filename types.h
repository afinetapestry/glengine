#ifndef __TYPES_H__
#define __TYPES_H__

#ifdef _CPLUSPLUS
extern "C" {
#endif

typedef unsigned int uint;

typedef struct int2 {
	int x;
	int y;
	
	int2() {x = y = 0;}
	int2(int _x, int _y) {x = _x; y = _y;}
} int2;

typedef struct int3 {
	int x;
	int y;
	int z;
	
	int3() {x = y = z = 0;}
	int3(int _x, int _y, int _z) {x = _x; y = _y; z = _z;}
} int3;

typedef struct int4 {
	int x;
	int y;
	int z;
	int w;
	
	int4() {x = y = z = w = 0;}
	int4(int _x, int _y, int _z) {x = _x; y = _y; z = _z; w = 255;}
	int4(int _x, int _y, int _z, int _w) {x = _x; y = _y; z = _z; w = _w;}
} int4;

#ifdef _CPLUSPLUS
}
#endif

#endif

