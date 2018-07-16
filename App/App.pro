#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T07:41:36
#
#-------------------------------------------------

TARGET = AudioScript

TEMPLATE = app

CONFIG += qt thread

DESTDIR = .

QT       += core widgets

INCLUDEPATH += \
    BlockArea \
    Editor \
    Main \
    ../ASUtils \
    ..

LIBS += \
    -L$$OUT_PWD/../ASUtils -lASUtils \ # dynamic library containing shared defs
    -L$$OUT_PWD/../Engine -lEngine \ # static library containing engine implementation
    -L$$OUT_PWD/../Compiler -lCompiler # static library containing compiler implementation

win32 {
    PRE_TARGETDEPS += \
        $$OUT_PWD/../ASUtils/ASUtils.dll \
        $$OUT_PWD/../Engine/Engine.lib \
        $$OUT_PWD/../Compiler/Compiler.lib
} else {
    PRE_TARGETDEPS += \
        $$OUT_PWD/../Engine/libEngine.a \
        $$OUT_PWD/../Compiler/libCompiler.a
    macx {
        PRE_TARGETDEPS += $$OUT_PWD/../ASUtils/libASUtils.dylib
    } else {
        PRE_TARGETDEPS += $$OUT_PWD/../ASUtils/libASUtils.so
    }
}

include(../Engine/libs.pri)

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
