#ifndef COM_APPA_LIB_H
#define COM_APPA_LIB_H

#include "COM_APPA205_global.h"
#include <QString>
#include <QStringList>

extern "C" {
/*LAMPHLIBSHARED_EXPORT void inputTest( const char* const str );
LAMPHLIBSHARED_EXPORT const char* outputTest();
LAMPHLIBSHARED_EXPORT QString oddUpper(const QString& str);*/


LAMPHLIBSHARED_EXPORT const char* getInfo(); //also create file with name of functions
LAMPHLIBSHARED_EXPORT const char* DLLMain(); //the same
LAMPHLIBSHARED_EXPORT const char* getFunctions();
LAMPHLIBSHARED_EXPORT bool createFile();

LAMPHLIBSHARED_EXPORT const char* checkPORT( const char* const port, const char* const info );
LAMPHLIBSHARED_EXPORT void setPORT( const char* const str );
LAMPHLIBSHARED_EXPORT void readData();


//LAMPHLIBSHARED_EXPORT void tuning( const char* const str );
//LAMPHLIBSHARED_EXPORT void sendParameters( const char* const str );
//LAMPHLIBSHARED_EXPORT void setParameters( const char* const str );


LAMPHLIBSHARED_EXPORT float getFloat();
LAMPHLIBSHARED_EXPORT const char* getUnit();
LAMPHLIBSHARED_EXPORT const char* getValue();  // Float + " " + Unit;
LAMPHLIBSHARED_EXPORT const char* getSN();




}

#endif // COM_APPA_LIB_H
