#-------------------------------------------------
#
# Project created by QtCreator 2012-07-01T00:03:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = login
TEMPLATE = app

unix{
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

win32{
    INCLUDEPATH += "C:/opencv/opencv/build/include/opencv" \
                   "C:/opencv/opencv/build/include"

    LIBS += "C:/opencv/lib/libopencv_core241.dll.a" \
            "C:/opencv/lib/libopencv_features2d241.dll.a" \
            "C:/opencv/lib/libopencv_flann241.dll.a" \
            "C:/opencv/lib/libopencv_highgui241.dll.a" \
            "C:/opencv/lib/libopencv_video241.dll.a" \
            "C:/opencv/lib/libopencv_imgproc241.dll.a"
}

SOURCES += main.cpp\
        login_widget.cpp \
    config_dialog.cpp \
    register_widget.cpp \
    opencv_widget.cpp \
    config_manager.cpp

HEADERS  += \
    config_dialog.h \
    register_widget.h \
    opencv_widget.h \
    login_widget.h \
    config_manager.h

TRANSLATIONS += ./translations/i18n_zh_CN.ts
