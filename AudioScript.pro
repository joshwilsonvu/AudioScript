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
    Backend/audioscript.cpp \
    Backend/audioscriptcompiler.cpp \
    Backend/audioscriptengine.cpp \
    Backend/audioscriptlibrary.cpp \
    Backend/audioscriptvariant.cpp \
    Backend/classloader.cpp \
    Backend/main.cpp \
    Frontend/applicationoutput.cpp \
    Frontend/audiocontrols.cpp \
    Frontend/audioscriptchain.cpp \
    Frontend/classwidget.cpp \
    Frontend/codeeditor.cpp \
    Frontend/codetabs.cpp \
    Frontend/dialogs.cpp \
    Frontend/mainwindow.cpp \
    Frontend/sidewidgetbase.cpp

HEADERS += \
    Backend/audioscript.h \
    Backend/audioscriptcompiler.h \
    Backend/audioscriptengine.h \
    Backend/audioscriptlibrary.h \
    Backend/audioscriptvariant.h \
    Backend/classloader.h \
    Frontend/applicationoutput.h \
    Frontend/audiocontrols.h \
    Frontend/audioscriptchain.h \
    Frontend/classwidget.h \
    Frontend/codeeditor.h \
    Frontend/codetabs.h \
    Frontend/dialogs.h \
    Frontend/mainwindow.h \
    Frontend/sidewidgetbase.h

FORMS += \
    Forms/mainwindow.ui

RESOURCES += \
    Resources/resources.qrc \
    Resources/style.qrc

INCLUDEPATH += \
    Backend \
    Frontend
