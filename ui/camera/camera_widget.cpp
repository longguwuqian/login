#include <QtGui>
#include <QDebug>
#include "camera_widget.h"

camera_widget::camera_widget(QWidget *parent, int device_number, QString border_file_path)
    : QWidget(parent)
{
    lb_frame = new QLabel(this);
    this->dev_num = device_number;
    cpt_thread = new capture_thread(this->dev_num);
    if (!border_file_path.isNull()) {
        this->cpt_thread->set_border_file(border_file_path);
    }

    connect(this->cpt_thread, SIGNAL(new_frame(QImage*, QMutex*, volatile bool*)),
            this, SLOT(update_frame(QImage*, QMutex*, volatile bool*)));
}

camera_widget::~camera_widget(void)
{
    this->cpt_thread->stop_capture_thread();
    this->cpt_thread->disconnect_camera();
    delete cpt_thread;
}

void camera_widget::update_frame(QImage *img_frame, QMutex *update_done_mutex, volatile bool *update_done)
{
    update_done_mutex->lock();
    this->lb_frame->setPixmap(QPixmap::fromImage(*img_frame));
    *update_done = true;
    update_done_mutex->unlock();
}

void camera_widget::connect_camera()
{
    this->cpt_thread->connect_camera(this->dev_num);
}

void camera_widget::disconnect_camera()
{
    cpt_thread->disconnect_camera();
}

bool camera_widget::is_camera_connected()
{
    return this->cpt_thread->is_camera_connected();
}

void camera_widget::start_capture_thread()
{
    this->cpt_thread->start_capture_thread();
}

void camera_widget::stop_capture_thread()
{
    cpt_thread->stop_capture_thread();
}

int camera_widget::get_input_source_width()
{
    return cpt_thread->get_input_source_width();
}

int camera_widget::get_input_source_height()
{
    return cpt_thread->get_input_source_height();
}
QImage& camera_widget::get_frame_qimage()
{
    return this->cpt_thread->get_frame_qimage();
}
IplImage *camera_widget::get_frame_iplimage()
{
    return this->cpt_thread->get_frame_iplimage();
}
