#-------------------------------------------------
#
# Project created by QtCreator 2018-07-13T15:02:25
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    monster.cpp \
    gameboundary1.cpp \
    gameboundary.cpp \
    person.cpp \
    gameboundary2.cpp \
    gameboundary3.cpp \
    store.cpp \
    gameboundary4.cpp \
    fighting.cpp

HEADERS += \
    monster.h \
    gameboundary1.h \
    gameboundary.h \
    person.h \
    global.h \
    gameboundary2.h \
    gameboundary3.h \
    store.h \
    gameboundary4.h \
    fighting.h

FORMS += \
    gameboundary1.ui \
    gameboundary.ui \
    gameboundary2.ui \
    gameboundary2.ui \
    gameboundary3.ui \
    store.ui \
    gameboundary4.ui \
    fighting.ui

RESOURCES += \
    resources.qrc
