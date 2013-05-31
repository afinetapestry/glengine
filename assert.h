#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <cassert>

#include <iostream>
#include <sstream>

#define ASSERT(condition) assert(condition)

#ifndef NDEBUG
#define ASSERTMSG(condition, message) \
	do { \
		if (!(condition)) { \
			std::ostringstream ostr; ostr << message; \
			std::cerr << "Assertion failed: " << #condition << ", function " << __func__ << ", file " << __FILE__ << ", line " << __LINE__ << ". " << std::endl << ostr.str() << std::endl; \
			std::abort(); \
		} \
	} while (false);
#else
#define ASSERT(condition, message) do {} while (false);
#endif

#endif

