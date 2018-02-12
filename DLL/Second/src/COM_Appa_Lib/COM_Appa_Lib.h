#ifndef COM_APPA_LIB_H
#define COM_APPA_LIB_H

#include "COM_Appa_Lib_global.h"
#include <QString>

extern "C" {
LAMPHLIBSHARED_EXPORT void inputTest( const char* const str );
LAMPHLIBSHARED_EXPORT const char* outputTest();
LAMPHLIBSHARED_EXPORT QString oddUpper(const QString& str);
}

#endif // COM_APPA_LIB_H
