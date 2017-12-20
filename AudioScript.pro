TEMPLATE = subdirs

CONFIG += debug c++11 warn_on

SUBDIRS = \
    ASUtils \
    App \
    BasicScript

App.depends = ASUtils
BasicScript.depends = ASUtils
