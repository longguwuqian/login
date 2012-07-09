#-------------------------------------------------
#
# Project created by QtCreator 2012-07-01T00:03:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = login
TEMPLATE = app

QMAKE_CXXFLAGS += -O3 -pipe -ftracer -fivopts -ftree-loop-linear -ftree-vectorize -ffast-math -march=native -mfpmath=sse -mmmx -msse -msse2 -mssse3 -msse4

unix{
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

#use qsingleapplication
include("./qtsingleapplication/src/qtsingleapplication.pri")
INCLUDEPATH += "./qtsingleapplication/src"

win32{
    INCLUDEPATH += "C:/opencv/opencv/build/include/opencv" \
                   "C:/opencv/opencv/build/include"

    LIBS += "C:/opencv/lib/libopencv_core241.dll.a" \
            "C:/opencv/lib/libopencv_features2d241.dll.a" \
            "C:/opencv/lib/libopencv_highgui241.dll.a" \
            "C:/opencv/lib/libopencv_video241.dll.a" \
}

SOURCES += main.cpp\
        login_widget.cpp \
    config_dialog.cpp \
    config_manager.cpp \
    capture_thread.cpp \
    camera_controller.cpp \
    camera_widget.cpp \
    face_detect.cpp

HEADERS  += \
    config_dialog.h \
    login_widget.h \
    config_manager.h \
    capture_thread.h \
    camera_controller.h \
    camera_widget.h \
    face_detect.h

TRANSLATIONS += ./translations/i18n_zh_CN.ts
