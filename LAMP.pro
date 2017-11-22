QT += widgets
QT += sql

HEADERS       = window.h \
    logowindow.h \
    authorization.h \
    sqlamp.h \
    initdb.h \
    experiments.h \
    database.h \
    dialogadddevice.h \
    mainwindow_test.h \
    table.h
SOURCES       = window.cpp \
                main.cpp \
    logowindow.cpp \
    authorization.cpp \
    sqlamp.cpp \
    experiments.cpp \
    database.cpp \
    dialogadddevice.cpp \
    mainwindow_test.cpp \
    table.cpp

FORMS    += mainwindow_test.ui \
    dialogadddevice.ui

DISTFILES += \
    conf.txt \
    README.md
