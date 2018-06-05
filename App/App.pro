#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T07:41:36
#
#-------------------------------------------------

include(../Common.pri)

TARGET = AudioScript

TEMPLATE = app

CONFIG += qt thread

DESTDIR = $$AS_TARGET_PATH

QT       += core widgets

INCLUDEPATH += \
    BlockArea \
    Editor \
    Main \
    ../ASUtils \
    ..

LIBS += -L$${AS_LIB_PATH} -l$${AS_LIB_NAME} # dynamic library containing shared defs

HEADERS += \
    BlockArea/audioblock.h \
    BlockArea/blockarea.h \
    Editor/applicationoutput.h \
    Editor/classdialog.h \
    Editor/classloader.h \
    Editor/codeeditor.h \
    Editor/codetabs.h \
    Editor/dialogs.h \
    Editor/scriptwindow.h \
    Main/mainwindow.h

SOURCES += \
    BlockArea/audioblock.cpp \
    BlockArea/blockarea.cpp \
    Editor/applicationoutput.cpp \
    Editor/classdialog.cpp \
    Editor/classloader.cpp \
    Editor/codeeditor.cpp \
    Editor/codetabs.cpp \
    Editor/dialogs.cpp \
    Editor/scriptwindow.cpp \
    Main/main.cpp \
    Main/mainwindow.cpp

FORMS += \
    Editor/scriptwindow.ui \
    Main/mainwindow.ui

DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += \
    Resources/resources.qrc \
    Resources/style.qrc

DISTFILES += \
    README.md
