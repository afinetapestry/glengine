#ifndef __GLEXCEPTION_HPP__
#define __GLEXCEPTION_HPP__

#include <string>

#define _glException() do {const char * err = _glError(); if (err != 0) {throw std::runtime_error(err);}} while (false);

#endif

