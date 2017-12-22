TEMPLATE = subdirs

CONFIG += c++11 warn_on

SUBDIRS = \
    ASUtils \
    App

App.depends = ASUtils
