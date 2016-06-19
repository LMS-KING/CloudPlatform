#-------------------------------------------------
#
# Project created by QtCreator 2015-11-19T20:36:39
#
#-------------------------------------------------

QT       += core gui

QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Teacher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    udpthread.cpp \
    freecontrol.cpp \
    signalcontrol.cpp \
    morecontrol.cpp \
    studentstatus.cpp \
    useways.cpp \
    prodouce.cpp

HEADERS  += mainwindow.h \
    udpthread.h \
    freecontrol.h \
    signalcontrol.h \
    morecontrol.h \
    studentstatus.h \
    useways.h \
    prodouce.h

FORMS    += mainwindow.ui \
    freecontrol.ui \
    signalcontrol.ui \
    morecontrol.ui \
    studentstatus.ui \
    useways.ui \
    prodouce.ui

RESOURCES += \
    Picture.qrc

RC_FILE += show.rc
