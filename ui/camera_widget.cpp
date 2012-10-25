#include <QtGui>
#include <QDebug>
#include "camera_widget.h"

camera_widget::camera_widget(QWidget *parent, int max_width, int max_height, int min_width, int min_height)
    : QWidget(parent)
{
    lb_frame = new QLabel(this);
    this->lb_frame->setMinimumSize(640, 480);
    this->setMinimumSize(640, 480);
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
