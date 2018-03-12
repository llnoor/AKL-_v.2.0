PROJECT_ROOT_PATH = $${PWD}/

DESTDIR = $${BIN_PATH}

win32: OS_SUFFIX = win32
linux-g++: OS_SUFFIX = linux

linux-g++: QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../lib.$${OS_SUFFIX}/

include( qwtWidgetLibrary.pri )

QT += widgets
QT += sql
QT += serialport

CONFIG += C++11

HEADERS       = window.h \
    logowindow.h \
    authorization.h \
    sqlamp.h \
    initdb.h \
    experiments.h \
    database.h \
    dialogauth.h \
    dialogreg.h \
    dialogexp.h \
    lamphplot.h \
    incrementalplot.h \
    mainplot.h \
    pixmaps.h \
    lamphsetting.h \
    lamphedit.h \
    datatable.h \
    lamphdevices.h
SOURCES       = window.cpp \
                main.cpp \
    logowindow.cpp \
    authorization.cpp \
    sqlamp.cpp \
    experiments.cpp \
    database.cpp \
    dialogauth.cpp \
    dialogreg.cpp \
    dialogexp.cpp \
    lamphplot.cpp \
    incrementalplot.cpp \
    mainplot.cpp \
    lamphsetting.cpp \
    lamphedit.cpp \
    datatable.cpp \
    lamphdevices.cpp


DISTFILES += \
    conf.txt \
    README.md \
    photo1.jpg \
    photo_sql.jpg

win32
{
    CONFIG += embed_manifest_exe
    QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:"level='requireAdministrator'"
}
