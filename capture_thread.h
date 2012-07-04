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
    void disconnect_camera();
    void stop_capture_thread();
    bool is_camera_connected();
    int get_input_source_width();
    int get_input_source_height();

    void cvimage2qimage(const IplImage* cvimage, QImage &qimage);

private:

    QImage img_frame;
    CvCapture *capture;
    QTime t;
    QMutex stopped_mutex;
    QMutex save_file_mutex;
    int capture_time;
    volatile bool stopped;
protected:
    void run();
signals:
    void new_frame(const QImage &frame);
};


#endif // CAPTURE_THREAD_H
