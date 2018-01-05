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
    globals.h \
    audioscriptui_p.h \
    bufferdata_p.h \
    audioscriptbuffer.h \
    audioscriptutils.h

SOURCES += \
    audioscriptui.cpp \
    audioscriptfactory.cpp \
    audioscript.cpp \
    audioscriptui_p.cpp \
    bufferdata_p.cpp \
    audioscriptbuffer.cpp \
    audioscriptutils.cpp

DEFINES += ASUTILS_LIBRARY # for windows import/export dll stuff
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DISTFILES += \
    AudioScript
