#include <QDebug>
#include "capture_thread.h"

capture_thread::capture_thread(int device_num):QThread()
{
    capture = cvCaptureFromCAM(device_num);
    stopped = false;
    update_done = true;
    this->img_border = new QImage("border.png");
    assert(!this->img_border->isNull());
}

void capture_thread::cvimage2qimage(const IplImage *cvimage, QImage &qimage)
{
    static IplImage *_cvimage;
    if (!cvimage)
        return;
    qimage = QImage(QSize(cvimage->width, cvimage->height), QImage::Format_RGB888);
    _cvimage = cvCreateImageHeader(cvSize(cvimage->width, cvimage->height), 8, 3);
    _cvimage->imageData = (char *)qimage.bits();
    cvCopy(cvimage, _cvimage, 0);
    cvCvtColor(_cvimage, _cvimage, CV_BGR2RGB);
}

void capture_thread::run()
{
    while(1) {
        stopped_mutex.lock();
        if (stopped) {
            stopped = false;
            stopped_mutex.unlock();
            break;
        }
        stopped_mutex.unlock();
        update_done_mutex.lock();
        while (!update_done) update_done_condition.wait(&update_done_mutex);
        update_done = false;
        this->cvimage2qimage(cvQueryFrame(capture), this->img_frame);
        _img_painter = new QPainter(&this->img_frame);
        _img_painter->setOpacity(0.4);
        _img_painter->drawImage(img_frame.width() / 2 - 170, img_frame.height() / 2 - 190, *this->img_border);
        _img_painter->end();
        delete _img_painter;
        emit new_frame(&this->img_frame, &this->update_done_mutex, &this->update_done_condition, &this->update_done);
        update_done_mutex.unlock();
    }
    qDebug() << "Stopping capture thread...";
}

QImage &capture_thread::get_frame()
{
    static QImage _img;
    _img = this->img_frame.copy(this->img_frame.width() / 2 - 170, this->img_frame.height() / 2 - 190, 300, 340);
    return _img;
}

void capture_thread::connect_camera(int device_num)
{
    if (!this->is_camera_connected() && this->stopped) {
        capture=cvCaptureFromCAM(device_num);
    }
}

void capture_thread::disconnect_camera()
{
    if (!this->stopped) this->stop_capture_thread();
    if (capture!=NULL) {
        cvReleaseCapture(&capture);
        if(capture==NULL)
            qDebug() << "Camera successfully disconnected.";
        else
            qDebug() << "ERROR: Camera could not be disconnected.";
    }
}

void capture_thread::stop_capture_thread()
{
    stopped_mutex.lock();
    stopped=true;
    stopped_mutex.unlock();
}

bool capture_thread::is_camera_connected()
{
    if(capture!=NULL)
        return true;
    else
        return false;
}

int capture_thread::get_input_source_width()
{
    return cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
}

int capture_thread::get_input_source_height()
{
    return cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
}
