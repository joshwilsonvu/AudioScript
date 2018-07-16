
TEMPLATE = lib

CONFIG += staticlib qt thread

QT += core

INCLUDEPATH += \
    ../ASUtils \
    3rdParty

HEADERS += \
    ../engine.h \
    processgraph.h \
    pluginlibrary.h \
    processor.h \
    plugin.h \
    3rdParty/RtAudio.h


SOURCES += \
    engine.cpp \
    processgraph.cpp \
    pluginlibrary.cpp \
    processor.cpp \
    plugin.cpp \
    3rdParty/RtAudio.cpp

LIBS += -L$$OUT_PWD/../ASUtils/ -lASUtils
DEPENDPATH += ../ASUtils

# Platform-specific APIs to compile for RtAudio
win32 {
    DEFINES += \
        __WINDOWS_DS__ \
        __WINDOWS_ASIO__ \
        __WINDOWS_WASAPI__
    HEADERS += \
        3rdParty/include/*.h
    SOURCES += \
        3rdParty/include/*.cpp  # for windows-specific necessary files
} else:macx {
    DEFINES += \
        __MACOSX_CORE__
} else:unix {
    DEFINES += \
        __LINUX_ALSA__ \
        __LINUX_PULSE__ \
        __LINUX_OSS__ \
        __UNIX_JACK

}

DISTFILES += \
    libs.pri

