#ifndef MYLIB_H
#define MYLIB_H

#include "mylib_global.h"

extern "C" {
MYLIBSHARED_EXPORT void inputTest( const char* const str );
MYLIBSHARED_EXPORT const char* outputTest();
}

#endif // MYLIB_H
