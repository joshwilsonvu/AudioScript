#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T07:41:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    Sources/Backend/audioscript.cpp \
    Sources/Backend/audioscriptcompiler.cpp \
    Sources/Backend/audioscriptengine.cpp \
    Sources/Backend/audioscriptlibrary.cpp \
    Sources/Backend/audioscriptvariant.cpp \
    Sources/Backend/classloader.cpp \
    Sources/Backend/main.cpp \
    Sources/Frontend/applicationoutput.cpp \
    Sources/Frontend/codeeditor.cpp \
    Sources/Frontend/codetabs.cpp \
    Sources/Frontend/dialogs.cpp \
    Sources/Frontend/mainwindow.cpp \
    Sources/Frontend/audioscriptchain.cpp \
    Sources/Frontend/audiocontrols.cpp

HEADERS += \
    Includes/Backend/audioscript.h \
    Includes/Backend/audioscriptcompiler.h \
    Includes/Backend/audioscriptengine.h \
    Includes/Backend/audioscriptlibrary.h \
    Includes/Backend/audioscriptvariant.h \
    Includes/Backend/classloader.h \
    Includes/Frontend/applicationoutput.h \
    Includes/Frontend/codeeditor.h \
    Includes/Frontend/codetabs.h \
    Includes/Frontend/dialogs.h \
    Includes/Frontend/mainwindow.h \
    Includes/Frontend/audioscriptchain.h \
    Includes/Frontend/audiocontrols.h

FORMS += \
    Forms/mainwindow.ui

RESOURCES += \
    Resources/resources.qrc

INCLUDEPATH += Sources/Backend \
    Sources/Frontend \
    Includes/Backend \
    Includes/Frontend
