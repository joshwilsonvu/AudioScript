TEMPLATE = subdirs

CONFIG += debug c++11 ordered

SUBDIRS = \
    LibAudioScript \
    App \
    BasicScript

App.depends += LibAudioScript
BasicScript.depends += LibAudioScript

