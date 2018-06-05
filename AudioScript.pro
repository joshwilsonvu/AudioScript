TEMPLATE = subdirs

CONFIG += c++11 warn_on

SUBDIRS = \
    ASUtils \
    App \
    Engine \
    Compiler

App.depends = ASUtils Engine Compiler
Engine.depends = ASUtils
