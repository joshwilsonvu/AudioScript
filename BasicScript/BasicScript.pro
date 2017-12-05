#-------------------------------------------------
#
# Project created by QtCreator 2017-11-22T12:53:57
#
#-------------------------------------------------

QT       -= gui

TARGET = BasicScript
TEMPLATE = lib
CONFIG += qt plugin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050902    # disables all the APIs deprecated before Qt 5.9.2

SOURCES += \
        basicscript.cpp \
        basicscriptfactory.cpp

HEADERS += \
        basicscript.h \
        basicscriptfactory.h

INCLUDEPATH += \
        ../App/User \
        ../App/Engine

unix {
    target.path = /usr/lib
    INSTALLS += target
}
