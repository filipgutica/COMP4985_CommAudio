#-------------------------------------------------
#
# Project created by QtCreator 2015-02-18T10:48:01
#
#-------------------------------------------------

QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += network

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        application.cpp \
    audioplayer.cpp \
    client.cpp \
    audiothread.cpp \
    configure.cpp \
    downloader.cpp

HEADERS  += application.h \
    audioplayer.h \
    client.h \
    audiothread.h \
    globals.h \
    configure.h \
    downloader.h

FORMS    += application.ui \
    audioplayer.ui \
    configure.ui \
    downloader.ui

CONFIG += static
