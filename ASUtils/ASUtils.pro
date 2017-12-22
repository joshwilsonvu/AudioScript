#-------------------------------------------------
#
# ASUtils - helper library containing code required
#     by the AudioScript app and AudioScript plugins
#
#-------------------------------------------------

TARGET = ASUtils

TEMPLATE = lib

CONFIG   += qt

DESTDIR = /Users/Josh/QProjects/Builds

QT       += core widgets

HEADERS += \
    audioscript.h \
    audioscriptfactory.h \
    audioscriptui.h \
    utils.h \
    globals.h

SOURCES += \
    audioscriptui.cpp \
    utils.cpp \
    audioscriptfactory.cpp \
    audioscript.cpp

DEFINES += ASUTILS_LIBRARY # for windows import/export dll stuff
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
