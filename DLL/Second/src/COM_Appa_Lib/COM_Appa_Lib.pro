#-------------------------------------------------
#
# Project created by QtCreator 2018-02-03
# Lib for LAMPh
#
#-------------------------------------------------

QT       -= gui

include( ../../common.pri )
include( ../../lib.pri )

TARGET = COM_Appa_Lib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += LAMPHLIB_LIBRARY

SOURCES += COM_Appa_Lib.cpp

HEADERS += COM_Appa_Lib.h\
        COM_Appa_Lib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
