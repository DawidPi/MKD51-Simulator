#-------------------------------------------------
#
# Project created by QtCreator 2015-03-07T16:41:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WLedPlugin
TEMPLATE = app


SOURCES += main.cpp\
        View/sources/buttonsmanager.cpp\
        View/sources/diode.cpp\
        View/sources/diodemanager.cpp\
        View/sources/keyboardbutton.cpp\
        View/sources/keyboardmanager.cpp\
        View/sources/potmanager.cpp\
        View/sources/singledigit.cpp\
        View/sources/mainview.cpp \
        View/sources/procview.cpp \
        View/sources/buzzer.cpp \
        View/sources/ledmanager.cpp \
        Controller/sources/simulator.cpp

HEADERS  += View/headers/buttonsmanager.h\
        View/headers/diode.h\
        View/headers/diodemanager.h\
        View/headers/keyboardbutton.h\
        View/headers/keyboardmanager.h\
        View/headers/potmanager.h\
        View/headers/singledigit.h\
        View/headers/mainview.h \
        View/headers/procview.h \
        View/headers/buzzer.h \
        View/headers/ledmanager.h \
        Controller/headers/simulator.h
