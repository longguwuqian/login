#include <QtGui>
#include <QDebug>
#include "camera_widget.h"
#include "config_manager.h"

camera_widget::camera_widget(QWidget *parent)
    : QWidget(parent)
{
    lb_frame = new QLabel(this);
    layout = new QVBoxLayout(this);
    layout->addWidget(lb_frame);
    this->setLayout(layout);
    this->lb_frame->setMinimumSize(config_manager::get_instance().get_face_width(), config_manager::get_instance().get_face_height());
    this->lb_frame->setMaximumSize(config_manager::get_instance().get_face_width(), config_manager::get_instance().get_face_height());
    this->setMinimumSize(config_manager::get_instance().get_camera_widget_width(), config_manager::get_instance().get_camera_widget_height());
    this->setMaximumSize(config_manager::get_instance().get_camera_widget_width(), config_manager::get_instance().get_camera_widget_height());
}

camera_widget::~camera_widget(void)
{
}

void camera_widget::update_frame(QImage *img_frame, QMutex *update_done_mutex, QWaitCondition *update_done_condition, volatile bool *update_done)
{
    update_done_mutex->lock();

    this->lb_frame->setPixmap(QPixmap::fromImage(*img_frame));
    *update_done = true;
    update_done_condition->wakeAll();
    update_done_mutex->unlock();
}
