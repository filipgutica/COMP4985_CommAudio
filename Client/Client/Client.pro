#-------------------------------------------------
#
# Project created by QtCreator 2015-02-18T10:48:01
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        application.cpp \
    audioplayer.cpp

HEADERS  += application.h \
    audioplayer.h \
    client.h

FORMS    += application.ui \
    audioplayer.ui
