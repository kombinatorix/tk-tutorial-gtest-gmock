#ifndef __exercise2__hpp__
#define __exercise2__hpp__

#include <exception>
struct NULLException : public std::exception {
	const char * what () const throw () {
		return "NULL Exception";
	}
};

void throws(int* a);





void throwsNot(int* a);

#endif
