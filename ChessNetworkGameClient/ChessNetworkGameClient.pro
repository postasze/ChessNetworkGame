#-------------------------------------------------
#
# Project created by QtCreator 2018-04-30T14:45:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessNetworkGameClient
TEMPLATE = app
CONFIG += console c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    chessgamewidget.cpp \
    figure.cpp \
    extendedgraphicsview.cpp \
    chesstable.cpp \
    logindialog.cpp \
    communicator.cpp \
    controller.cpp

HEADERS += \
        mainwindow.h \
    chessgamewidget.h \
    constants.h \
    figure.h \
    extendedgraphicsview.h \
    chesstable.h \
    logindialog.h \
    communicator.h \
    controller.h

FORMS += \
    mainwindow.ui \
    chesstable.ui \
    logindialog.ui

RESOURCES += \
    images.qrc
