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
    face_recognition.cpp \
    face_recognition/MatrixOper.cpp \
    face_recognition/AffineTrans.cpp

HEADERS  += \
    config_dialog.h \
    login_widget.h \
    config_manager.h \
    capture_thread.h \
    camera_controller.h \
    camera_widget.h \
    face_recognition.h \
    face_recognition/MemoryOper.h \
    face_recognition/MatrixOper.h \
    face_recognition/BasicDataType.h \
    face_recognition/AffineTrans.h

TRANSLATIONS += ./translations/i18n_zh_CN.ts

HEADERS += \
    tcp_sender.h

SOURCES += \
    tcp_sender.cpp
