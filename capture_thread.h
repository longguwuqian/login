#ifndef CAPTURE_THREAD_H
#define CAPTURE_THREAD_H

// Qt header files
#include <QThread>
#include <QtGui>
// OpenCV header files
#include "highgui.h"
#include "cv.h"

class capture_thread : public QThread
{
    Q_OBJECT

public:
    capture_thread(int device_num);
    void connect_camera(int device_num);
    void disconnect_camera();
    void stop_capture_thread();
    bool is_camera_connected();
    int get_input_source_width();
    int get_input_source_height();
    QImage &get_frame();

    void cvimage2qimage(const IplImage* cvimage, QImage &qimage);

private:
    QImage img_frame;
    CvCapture *capture;
    QMutex stopped_mutex;
    volatile bool stopped;
protected:
    void run();
signals:
    void new_frame(QImage *frame);
};


#endif // CAPTURE_THREAD_H
