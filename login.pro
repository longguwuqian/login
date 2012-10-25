#-------------------------------------------------
#
# Project created by QtCreator 2012-07-01T00:03:03
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = login
TEMPLATE = app

QMAKE_CXXFLAGS += -O3 -pipe -ftracer -fivopts -ftree-loop-linear -ftree-vectorize -ffast-math -march=native -mfpmath=sse -mmmx -msse -msse2 -mssse3 -msse4



#use qsingleapplication
include("./qtsingleapplication/src/qtsingleapplication.pri")
INCLUDEPATH += "./qtsingleapplication/src"

unix{
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}
win32{
    INCLUDEPATH += "C:/opencv/opencv/build/include/opencv" \
                   "C:/opencv/opencv/build/include"

    LIBS += "C:/opencv/lib/libopencv_core241.dll.a" \
            "C:/opencv/lib/libopencv_features2d241.dll.a" \
            "C:/opencv/lib/libopencv_highgui241.dll.a" \
            "C:/opencv/lib/libopencv_video241.dll.a" \
            "C:/opencv/lib/libopencv_imgproc241.dll.a"
}

SOURCES += main.cpp\
    config_manager.cpp \
    capture_thread.cpp \
    camera_controller.cpp \

HEADERS  += \
    config_manager.h \
    capture_thread.h \
    camera_controller.h \

TRANSLATIONS += ./translations/i18n_zh_CN.ts

HEADERS += \
    tcp_sender.h

SOURCES += \
    tcp_sender.cpp

HEADERS += \
    ui/login_widget.h \
    ui/config_dialog.h \
    ui/camera_widget.h

SOURCES += \
    ui/login_widget.cpp \
    ui/config_dialog.cpp \
    ui/camera_widget.cpp

HEADERS += \
    login_client.h

SOURCES += \
    login_client.cpp
