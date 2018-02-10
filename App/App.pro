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
    Audio \
    BlockArea \
    Compilation \
    Editor \
    Engine \
    Main \
    ../ASUtils \
    Plugins \
    3rdParty

LIBS += -L$${AS_LIB_PATH} -l$${AS_LIB_NAME} \ # dynamic library containing shared defs
    -L$${PWD}/3rdParty -lrtaudio # dynamic library containing realtime audio code, must be remade on other systems

HEADERS += \
    3rdParty/RtAudio.h \
    Audio/rtwrapper.h \
    BlockArea/audioblock.h \
    BlockArea/blockarea.h \
    Compilation/audioscriptcompiler.h \
    Editor/applicationoutput.h \
    Editor/classdialog.h \
    Editor/classloader.h \
    Editor/codeeditor.h \
    Editor/codetabs.h \
    Editor/dialogs.h \
    Editor/scriptwindow.h \
    Engine/audioscriptengine.h \
    Engine/audioscriptplugin.h \
    Main/mainwindow.h

SOURCES += \
    Audio/rtwrapper.cpp \
    BlockArea/audioblock.cpp \
    BlockArea/blockarea.cpp \
    Compilation/audioscriptcompiler.cpp \
    Editor/applicationoutput.cpp \
    Editor/classdialog.cpp \
    Editor/classloader.cpp \
    Editor/codeeditor.cpp \
    Editor/codetabs.cpp \
    Editor/dialogs.cpp \
    Editor/scriptwindow.cpp \
    Engine/audioscriptengine.cpp \
    Engine/audioscriptplugin.cpp \
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
