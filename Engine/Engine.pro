
TEMPLATE = lib

CONFIG += staticlib qt thread

QT += core

INCLUDEPATH += \
    ../ASUtils

HEADERS += \
    ../engine.h \
    plugin.h \
    3rdParty/RtAudio.h \
    processgraph.h \
    pluginlibrary.h \
    processor.h

SOURCES += \
    engine.cpp \
    plugin.cpp \
    3rdParty/RtAudio.cpp \
    processgraph.cpp \
    pluginlibrary.cpp \
    processor.cpp

LIBS += -L../ASUtils -lASUtils

# Platform-specific APIs to compile for RtAudio
win32 {
    DEFINES += \
        __WINDOWS_DS__ \
        __WINDOWS_ASIO__ \
        __WINDOWS_WASAPI__
    SOURCES += \
        3rdParty/include/*  # for windows-specific necessary files
    LIBS += \
        -lole32 \
        -lwinmm \
        -ldsound
} else:macx {
    DEFINES += \
        __MACOSX_CORE__
    LIBS += -framework CoreAudio  # link to CoreAudio framework
} else:unix {
    DEFINES += \
        __LINUX_ALSA__ \
        __LINUX_PULSE__ \
        __LINUX_OSS__ \
        __UNIX_JACK
    LIBS +=  \ # link to appropriate libraries, at least one
        -lasound \
        -lpulse-simple \
        -lpulse
}
