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
    INCLUDEPATH += "C:/opencv/build/include/opencv" \
                   "C:/opencv/build/include" \
                   "C:/opencv/build/include/opencv2"

    LIBS += "C:/opencv/build/x86/mingw/lib/libopencv_core244.dll.a" \
            "C:/opencv/build/x86/mingw/lib/libopencv_features2d244.dll.a" \
            "C:/opencv/build/x86/mingw/lib/libopencv_highgui244.dll.a" \
            "C:/opencv/build/x86/mingw/lib/libopencv_video244.dll.a" \
            "C:/opencv/build/x86/mingw/lib/libopencv_imgproc244.dll.a" \
            "C:/opencv/build/x86/mingw/lib/libopencv_contrib244.dll.a" \
            "C:/opencv/build/x86/mingw/lib/libopencv_objdetect244.dll.a"
}

SOURCES += main.cpp\
    config_manager.cpp \
    http_sender.cpp \
    face_recognizer/my_eigen_face_recognizer.cpp \
    face_recognizer/face_recognizer.cpp \
    face_detector/MatrixOper.cpp \
    face_detector/face_detector.cpp \
    face_detector/AffineTrans.cpp

HEADERS  += \
    config_manager.h \
    http_sender.h \
    face_recognizer/my_eigen_face_recognizer.h \
    face_recognizer/face_recognizer.h \
    face_detector/MemoryOper.h \
    face_detector/MatrixOper.h \
    face_detector/face_detector.h \
    face_detector/BasicDataType.h \
    face_detector/AffineTrans.h

TRANSLATIONS += ./translations/i18n_zh_CN.ts

HEADERS +=

SOURCES +=

HEADERS += \
    ui/login_widget.h \
    ui/config_dialog.h \

SOURCES += \
    ui/login_widget.cpp \
    ui/config_dialog.cpp \

HEADERS += \
    login_client.h

SOURCES += \
    login_client.cpp

HEADERS += \
    ui/camera/capture_thread.h \
    ui/camera/camera_widget.h \

SOURCES += \
    ui/camera/capture_thread.cpp \
    ui/camera/camera_widget.cpp \

