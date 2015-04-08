#-------------------------------------------------
#
# Project created by QtCreator 2015-04-04T13:12:44
#
#-------------------------------------------------

QT       += widgets declarative qml quick network opengl sql script scripttools svg webkit webkitwidgets xml xmlpatterns multimedia testlib

TARGET = MKD51_Plugin
TEMPLATE = lib

DEFINES += MKD51_PLUGIN_LIBRARY

SOURCES += mkd51_plugin.cpp \

HEADERS += mkd51_plugin.h\
        mkd51_plugin_global.h \
        AGSI.h \
        AGSI_Defs.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
