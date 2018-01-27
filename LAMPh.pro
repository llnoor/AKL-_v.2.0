QT += widgets
QT += sql

HEADERS       = window.h \
    logowindow.h \
    authorization.h \
    sqlamp.h \
    initdb.h \
    experiments.h \
    database.h \
    dialogauth.h \
    dialogreg.h \
    dialogexp.h
SOURCES       = window.cpp \
                main.cpp \
    logowindow.cpp \
    authorization.cpp \
    sqlamp.cpp \
    experiments.cpp \
    database.cpp \
    dialogauth.cpp \
    dialogreg.cpp \
    dialogexp.cpp


DISTFILES += \
    conf.txt \
    README.md \
    photo1.jpg \
    photo_sql.jpg
