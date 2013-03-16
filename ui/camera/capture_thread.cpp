#include <QDebug>
#include "capture_thread.h"
#include <iostream>

capture_thread::capture_thread(int device_num):QThread()
{
    capture = cvCaptureFromCAM(device_num);
    stopped = true;
    update_done = true;
    _img_painter = new QPainter();
    this->img_border = NULL;
}
capture_thread::~capture_thread()
{
    delete _img_painter;
    delete img_border;
    disconnect_camera();
}
void capture_thread::set_border_file(QString border_file_path)
{
    this->img_border = new QImage(border_file_path);
//    assert(!this->img_border->isNull());
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
    cvReleaseImageHeader(&_cvimage);
}

void capture_thread::run()
{
    while(1) {
        stopped_mutex.lock();
        if (stopped) {
            stopped_mutex.unlock();
            break;
        }
        stopped_mutex.unlock();
        update_done_mutex.lock();
        if (!update_done) {
            update_done_mutex.unlock();
            continue;
        }
        update_done = false;
        this->cvimage2qimage(cvQueryFrame(capture), this->img_frame);
        this->orig_img_frame = this->img_frame;
        if (this->img_border != NULL) {
            _img_painter->begin(&this->img_frame);
            _img_painter->setOpacity(0.4);
            _img_painter->drawImage(0, 0, *this->img_border);
            _img_painter->end();
        }
        emit new_frame(&this->img_frame, &this->update_done_mutex, &this->update_done);
        update_done_mutex.unlock();
    }
    qDebug() << "Stopping capture thread...";
}

QImage &capture_thread::get_frame_qimage()
{
    static QImage _img;
    this->stop_capture_thread();
    _img = this->orig_img_frame.copy(0, 0, this->orig_img_frame.width(), this->orig_img_frame.height());
    this->start_capture_thread();
    return _img;
}

IplImage *capture_thread::get_frame_iplimage()
{
    static IplImage *_img = NULL;
    if (_img != NULL) cvReleaseImage(&_img);
    this->stop_capture_thread();
    _img = cvCloneImage(cvQueryFrame(capture));
    this->start_capture_thread();
    return _img;
}

void capture_thread::connect_camera(int device_num)
{
    if (!this->is_camera_connected() && !this->stopped) {
        capture=cvCaptureFromCAM(device_num);
    }
}

void capture_thread::disconnect_camera()
{
    this->stop_capture_thread();
    if (capture!=NULL) {
        cvReleaseCapture(&capture);
        if(capture==NULL)
            qDebug() << "Camera successfully disconnected.";
        else
            qDebug() << "ERROR: Camera could not be disconnected.";
    }
}

void capture_thread::start_capture_thread()
{
    qDebug() << "About to start capture thread...";
    stopped_mutex.lock();
    if (this->stopped) this->stopped = false;
    stopped_mutex.unlock();
    start();
}

void capture_thread::stop_capture_thread()
{
    qDebug() << "About to stop capture thread...";
    stopped_mutex.lock();
    if (!this->stopped) {
        stopped=true;
        stopped_mutex.unlock();
        wait();
    } else {
        stopped_mutex.unlock();
    }
    qDebug() << "Capture thread successfully stopped.";
}

bool capture_thread::is_camera_connected()
{
    if (capture!=NULL)
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
