#include "camera_controller.h"

// Qt header files
#include <QtGui>

camera_controller::camera_controller(int device_num)
{
    cpt_thread = new capture_thread(device_num);
    this->dev_num = device_num;
} // Controller constructor

camera_controller::~camera_controller()
{
    // Delete image buffer
    cpt_thread->disconnect_camera();
} // Controller destructor

void camera_controller::connect_camera()
{
    this->cpt_thread->connect_camera(this->dev_num);
}

void camera_controller::disconnect_camera()
{
    cpt_thread->disconnect_camera();
} // disconnectCamera()

bool camera_controller::is_camera_connected()
{
    return this->cpt_thread->is_camera_connected();
}

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




