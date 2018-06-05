#-------------------------------------------------
#
# ASUtils - helper library containing code required
#     by the AudioScript app and AudioScript plugins
#
#-------------------------------------------------

include(../Common.pri)

TARGET = $$AS_LIB_NAME

TEMPLATE = lib

CONFIG   += qt

DESTDIR = $$AS_LIB_PATH

QT       += core widgets

HEADERS += \
    script.h \
    factory.h \
    globals.h \
    buffer.h \
    utils.h \
    buffer.tpp \
    exception.h \
    #ui.h
    log.h

SOURCES += \
    factory.cpp \
    script.cpp \
    buffer.cpp \
    utils.cpp \
    exception.cpp \
    #ui.cpp \
    log.cpp

DEFINES += ASUTILS_LIBRARY # for windows import/export dll stuff
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DISTFILES += \
    AudioScript
