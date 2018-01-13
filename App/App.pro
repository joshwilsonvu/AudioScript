#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T07:41:36
#
#-------------------------------------------------

TARGET = AudioScript

TEMPLATE = app

CONFIG += qt thread

DESTDIR = /Users/Josh/QProjects/Builds

QT       += core widgets multimedia

INCLUDEPATH += \
    Audio \
    BlockArea \
    Compilation \
    Editor \
    Engine \
    Main \
    ../ASUtils \
    Plugins

ASUTILS_LIB_PATH = /Users/Josh/QProjects/Builds/
ASUTILS_LIB_NAME = ASUtils
LIBS += -L$${ASUTILS_LIB_PATH} -l$${ASUTILS_LIB_NAME}
PRE_TARGETDEPS += $${ASUTILS_LIB_PATH}$${ASUTILS_LIB_NAME}

HEADERS += \
    Audio/audioinput.h \
    Audio/audiooutput.h \
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
    Main/mainwindow.h \
    Audio/audiosettings.h \
    Audio/audioformat.h \
    Audio/audiosource.h \
    Audio/audiofilesource.h

SOURCES += \
    Audio/audioinput.cpp \
    Audio/audiooutput.cpp \
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
    Main/mainwindow.cpp \
    Audio/audiosettings.cpp \
    Audio/audioformat.cpp \
    Audio/audiosource.cpp \
    Audio/audiofilesource.cpp

FORMS += \
    Editor/scriptwindow.ui \
    Main/mainwindow.ui

DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += \
    Resources/resources.qrc \
    Resources/style.qrc

DISTFILES += \
    README.md
