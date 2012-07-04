#include "camera_controller.h"

// Qt header files
#include <QtGui>

camera_controller::camera_controller(int device_num)
{
    cpt_thread = new capture_thread(device_num);
} // Controller constructor

camera_controller::~camera_controller()
{
    // Delete image buffer
    cpt_thread->disconnect_camera();
} // Controller destructor

void camera_controller::disconnect_camera()
{
    cpt_thread->disconnect_camera();
} // disconnectCamera()

void camera_controller::start_capture_thread()
{
    this->cpt_thread->start();
}

void camera_controller::stop_capture_thread()
{
    qDebug() << "About to stop capture thread...";
    cpt_thread->stop_capture_thread();
    // Take one frame off a FULL queue to allow the capture thread to finish
    cpt_thread->wait();
    qDebug() << "Capture thread successfully stopped.";
} // stopCaptureThread()

void camera_controller::delete_capture_thread()
{
    // Delete thread
    delete cpt_thread;
} // deleteCaptureThread()

int camera_controller::get_input_source_width()
{
    return cpt_thread->get_input_source_width();
} // getInputSourceWidth()

int camera_controller::get_input_source_height()
{
    return cpt_thread->get_input_source_height();
} // getInputSourceHeight()




