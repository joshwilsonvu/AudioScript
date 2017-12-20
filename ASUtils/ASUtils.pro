#-------------------------------------------------
#
# Project created by QtCreator 2017-12-13T23:57:52
#
#-------------------------------------------------

QT       += widgets
QT       -= gui

TARGET = ASUtils
DESTDIR = /Users/Josh/QProjects/Builds
TEMPLATE = lib

DEFINES += ASUTILS_LIBRARY # for windows import/export dll stuff

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
    audioscriptui.cpp \
    utils.cpp \
    audioscriptfactory.cpp \
    audioscript.cpp

HEADERS += \
    audioscript.h \
    audioscriptfactory.h \
    audioscriptui.h \
    utils.h \
    globals.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
