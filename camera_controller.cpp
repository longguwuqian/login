#include <QDebug>
#include "camera_controller.h"

camera_controller::camera_controller(int device_num)
{
    cpt_thread = new capture_thread(device_num);
    this->dev_num = device_num;
}

camera_controller::~camera_controller()
{
    cpt_thread->stop_capture_thread();
    cpt_thread->disconnect_camera();
    delete_capture_thread();
}

void camera_controller::connect_camera()
{
    this->cpt_thread->connect_camera(this->dev_num);
}

void camera_controller::disconnect_camera()
{
    cpt_thread->disconnect_camera();
}

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
    cpt_thread->wait();
    qDebug() << "Capture thread successfully stopped.";
}

void camera_controller::delete_capture_thread()
{
    delete cpt_thread;
}

int camera_controller::get_input_source_width()
{
    return cpt_thread->get_input_source_width();
}

int camera_controller::get_input_source_height()
{
    return cpt_thread->get_input_source_height();
}
