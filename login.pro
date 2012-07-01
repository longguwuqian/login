#-------------------------------------------------
#
# Project created by QtCreator 2012-07-01T00:03:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = login
TEMPLATE = app

CONFIG += link_pkgconfig
PKGCONFIG += opencv

SOURCES += main.cpp\
        login_widget.cpp \
    QOpenCVWidget.cpp

HEADERS  += login_widget.h \
    QOpenCVWidget.h

FORMS    += loginwidget.ui
