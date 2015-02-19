#-------------------------------------------------
#
# Project created by QtCreator 2015-02-18T10:27:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        application.cpp \
        configure.cpp \
        server.cpp

HEADERS  += application.h \
        configure.h \
        server.h

FORMS    += application.ui \
        configure.ui
