QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_servertest.cpp \
    ../chessmatch.cpp \
    ../chesstable.cpp \
    ../clienthandler.cpp \
    ../controller.cpp \
    ../figure.cpp \
    ../communicator.cpp

SUBDIRS += \
    ../ChessNetworkGameServer.pro

DISTFILES += \
    ../ChessNetworkGameServer.pro.user

HEADERS += \
    ../chessmatch.h \
    ../chesstable.h \
    ../controller.h \
    ../figure.h \
    ../constants.h \
    ../communicator.h \
    ../clienthandler.h
