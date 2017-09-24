QT += widgets
QT += sql

HEADERS       = window.h \
    logowindow.h \
    authorization.h \
    sqlamp.h \
    initdb.h
SOURCES       = window.cpp \
                main.cpp \
    logowindow.cpp \
    authorization.cpp \
    sqlamp.cpp

DISTFILES += \
    conf.txt \
    README.md
