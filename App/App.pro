#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T07:41:36
#
#-------------------------------------------------

TARGET = AudioScript

TEMPLATE = app

CONFIG += qt

DESTDIR = /Users/Josh/QProjects/Builds

QT       += core widgets

#QMAKE_MAC_SDK = macosx10.12

INCLUDEPATH += \
    BlockArea \
    Compilation \
    Editor \
    Engine \
    Main \
    ../ASUtils \
    Plugins

LIBS += -L/Users/Josh/QProjects/Builds/ -lASUtils

HEADERS += \
    BlockArea/audioblock.h \
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
    Main/mainwindow.h \
    #Engine/audioscriptvariant.h

SOURCES += \
    BlockArea/audioblock.cpp \
    Compilation/audioscriptcompiler.cpp \
    Editor/applicationoutput.cpp \
    Editor/classdialog.cpp \
    Editor/classloader.cpp \
    Editor/codeeditor.cpp \
    Editor/codetabs.cpp \
    Editor/dialogs.cpp \
    Editor/scriptwindow.cpp \
    Engine/audioscriptengine.cpp \
    Main/main.cpp \
    Main/mainwindow.cpp \
    Engine/audioscriptplugin.cpp \
    #Engine/audioscriptvariant.cpp \

FORMS += \
    Editor/scriptwindow.ui \
    Main/mainwindow.ui

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050902    # disables all the APIs deprecated before Qt 5.9.2









RESOURCES += \
    Resources/resources.qrc \
    Resources/style.qrc





DEFINES += \
    QT_NO_PLUGIN_CHECK # until we figure out why plugins aren't loading

DISTFILES += \
    README.md
