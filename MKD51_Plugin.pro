#-------------------------------------------------
#
# Project created by QtCreator 2015-04-04T13:12:44
#
#-------------------------------------------------

QT       += widgets declarative qml quick network opengl sql script scripttools svg webkit webkitwidgets xml xmlpatterns multimedia testlib

QMAKE_CXXFLAGS += -std=c++11 -fno-exceptions

TARGET = MKD51_Plugin
TEMPLATE = lib

DEFINES += MKD51_PLUGIN_LIBRARY

SOURCES += mkd51_plugin.cpp \
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
        Controller/sources/simulator.cpp \
        Controller/sources/guistart.cpp \
        Model/sources/keillistener.cpp \
        Model/sources/guilistener.cpp \

HEADERS += mkd51_plugin.h\
        mkd51_plugin_global.h \
        AGSI.h \
        AGSI_Defs.h \
        View/headers/buttonsmanager.h\
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
        Controller/headers/simulator.h \
        Controller/headers/guistart.h \
        Model/headers/keillistener.h \
        Model/headers/guilistener.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
