#ifndef CAPTURE_THREAD_H
#define CAPTURE_THREAD_H
#include <QThread>
#include <QImage>
#include <QMutex>
#include <QWaitCondition>
#include <QPainter>
#include "opencv/highgui.h"
#include "opencv/cv.h"

class capture_thread : public QThread
{
    Q_OBJECT

public:
    capture_thread(int device_num);
    ~capture_thread();
    void connect_camera(int device_num);
    void disconnect_camera();
    void start_capture_thread();
    void stop_capture_thread();
    bool is_camera_connected();
    int get_input_source_width();
    int get_input_source_height();
    QImage &get_frame_qimage();
    IplImage *get_frame_iplimage();
    void set_border_file(QString border_file_path);
    void cvimage2qimage(const IplImage* cvimage, QImage &qimage);
private:
    QString border_file_path;
    QImage *img_border;
    QImage img_frame;
    QImage orig_img_frame;
    QPainter *_img_painter;
    CvCapture *capture;
    QMutex stopped_mutex;
    QMutex update_done_mutex;
    volatile bool update_done;
    volatile bool stopped;
protected:
    void run();
signals:
    void new_frame(QImage *frame, QMutex *update_done_mutex, volatile bool *update_done);
};

#endif // CAPTURE_THREAD_H
