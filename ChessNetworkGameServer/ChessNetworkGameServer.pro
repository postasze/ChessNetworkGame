TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += thread

SOURCES += main.cpp \
    clienthandler.cpp \
    communicator.cpp \
    controller.cpp \
    chesstable.cpp

HEADERS += \
    constants.h \
    clienthandler.h \
    communicator.h \
    controller.h \
    chesstable.h
