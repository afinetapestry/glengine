#ifndef __GLEXCEPTION_HPP__
#define __GLEXCEPTION_HPP__

#define _glException() do {const char * err = _glError(); if (err != 0) {throw err;}} while (false);

#endif

