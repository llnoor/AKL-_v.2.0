#-------------------------------------------------
#
# Project created by QtCreator 2016-09-12T09:44:19
#
#-------------------------------------------------

QT       -= gui

include( ../../common.pri )
include( ../../lib.pri )

TARGET = MyLib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += MYLIB_LIBRARY

SOURCES += mylib.cpp

HEADERS += mylib.h\
        mylib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
