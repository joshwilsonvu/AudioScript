project(AudioScript)
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

set(COMPILE_OPTIONS -std=c++11)

set(APP_INCLUDES \
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
    )

set(APP_SOURCES \
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
    Engine/audioscriptplugin.cpp \
    Main/main.cpp \
    Main/mainwindow.cpp \
    )

add_library(${ SHARED ${APP_SOURCES})
add_executable(AudioScript main.cpp)

target_link_libraries(test-plugin PRIVATE Qt5::Widgets)
target_compile_options(test-plugin PRIVATE ${COMPILE_OPTIONS})

target_link_libraries(test-plugin-exec PRIVATE Qt5::Widgets)
target_compile_options(test-plugin-exec PRIVATE ${COMPILE_OPTIONS})
