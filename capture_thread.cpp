#include "capture_thread.h"


// Qt header files
#include <QDebug>

capture_thread::capture_thread(int device_num):QThread()
{
    // Open camera
    capture=cvCaptureFromCAM(device_num);
    // Initialize variables
    stopped=false;
} // CaptureThread constructor



void capture_thread::cvimage2qimage(const IplImage *cvimage, QImage &qimage)
{
    static IplImage *_cvimage;
    if (!cvimage)
            return;
    qimage = QImage(QSize(cvimage->width, cvimage->height), QImage::Format_RGB888);
            // IplImage * to work with OpenCV functions
    _cvimage = cvCreateImageHeader(cvSize(cvimage->width, cvimage->height), 8, 3);
            // Share the buffer between QImage and IplImage *
    _cvimage->imageData = (char *)qimage.bits();
    cvCopy(cvimage, _cvimage, 0);
        // Convert it from BGR to RGB. QImage works with RGB and cvQueryFrame returns a BGR IplImage
    cvCvtColor(_cvimage, _cvimage, CV_BGR2RGB);
}


void capture_thread::run()
{
    while(1)
    {
        stopped_mutex.lock();
        if (stopped)
        {
            stopped=false;
            stopped_mutex.unlock();
            break;
        }
        stopped_mutex.unlock();
        // Capture and add frame to buffer
        this->cvimage2qimage(cvQueryFrame(capture), this->img_frame);
        emit new_frame(this->img_frame);
        // Update statistics
    }
    qDebug() << "Stopping capture thread...";
} // run()

QImage &capture_thread::get_frame()
{
    static QImage _img;
    _img = this->img_frame;
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
    // Disconnect camera if connected
    if (!this->stopped) this->stop_capture_thread();
    if (capture!=NULL)
    {
        cvReleaseCapture(&capture);
        if(capture==NULL)
            qDebug() << "Camera successfully disconnected.";
        else
            qDebug() << "ERROR: Camera could not be disconnected.";
    }
} // disconnectCamera()


void capture_thread::stop_capture_thread()
{
    stopped_mutex.lock();
    stopped=true;
    stopped_mutex.unlock();
} // stopCaptureThread()


bool capture_thread::is_camera_connected()
{
    if(capture!=NULL)
        return true;
    else
        return false;
} // isCameraConnected()

int capture_thread::get_input_source_width()
{
    return cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
} // getInputSourceWidth()

int capture_thread::get_input_source_height()
{
    return cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
} // getInputSourceHeight()
