TEMPLATE = subdirs

CONFIG += c++11 warn_on

SUBDIRS = \
    ASUtils \
    App \
    Engine \
    Compilation

App.depends = ASUtils
