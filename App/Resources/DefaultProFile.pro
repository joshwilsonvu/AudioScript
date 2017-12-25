# The lib template and plugin configuration allow AudioScript
# to load and run user code.

TARGET = SCRIPTNAME
TEMPLATE = lib
CONFIG += plugin c++11
DESTDIR = /Users/Josh/QProjects/Builds
INCLUDEPATH += ../AudioScript/ASUtils
LIBS += -L/Users/Josh/QProjects/Builds/ -lASUtils
HEADERS += \
        SCRIPTNAME.h \
        SCRIPTNAMEfactory.h
SOURCES += \
        SCRIPTNAME.cpp \
        SCRIPTNAMEfactory.cpp
DEFINES += QT_DEPRECATED_WARNINGS

