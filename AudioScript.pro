#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T07:41:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_MAC_SDK = macosx10.12

TARGET = AudioScript
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += qt debug

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
    Engine/audioscriptlibrary.cpp \
    Engine/audioscriptvariant.cpp \
    Main/main.cpp \
    Main/mainwindow.cpp \
    User/utils.cpp \
    User/audioscriptgui.cpp


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
    Engine/audioscriptlibrary.h \
    Engine/audioscriptvariant.h \
    Main/mainwindow.h \
    User/audioscript.h \
    User/utils.h \
    User/audioscriptfactory.h \
    User/audioscriptgui.h


FORMS += \
    Editor/scriptwindow.ui \
    Main/mainwindow.ui


RESOURCES += \
    Resources/resources.qrc \
    Resources/style.qrc

INCLUDEPATH += \
    BlockArea \
    Compilation \
    Editor \
    Engine \
    Main \
    User \
    Plugins

DEFINES +=

DISTFILES += \
    README.md
