#include <QtGui>
#include "camera_widget.h"

// Constructor
camera_widget::camera_widget(QWidget *parent, int max_width, int max_height, int min_width, int min_height)
    : QWidget(parent)
{
    lb_frame = new QLabel(this);
    this->lb_frame->setMaximumSize(max_width, max_height);
    this->lb_frame->setMinimumSize(min_width, min_height);
    this->setMaximumSize(max_width + 10, max_height + 10);
    this->setMinimumSize(min_width + 10, min_height + 10);

    this->camera_ctlr = new camera_controller(0);
    this->camera_ctlr->start_capture_thread();

    connect(this->camera_ctlr->cpt_thread, SIGNAL(new_frame(QImage)), this, SLOT(update_frame(QImage)));
}

camera_widget::~camera_widget(void)
{
    this->camera_ctlr->stop_capture_thread();
    if (camera_ctlr != NULL) delete camera_ctlr;
}

void camera_widget::save_image()
{
//    QString path = QFileDialog::getSaveFileName((QWidget *)this->parent(), tr("save file dialog"), ".", tr("*.png"));
//    if (path != NULL) img.save(path);
}
void camera_widget::set_enable(bool b)
{

}
void camera_widget::set_disable(bool b)
{

}

bool camera_widget::is_enabled()
{
    return true;
}

bool camera_widget::is_disabled()
{
    return false;
}

void camera_widget::update_frame(const QImage &img_frame)
{
    this->lb_frame->setPixmap(QPixmap::fromImage(img_frame.scaled(lb_frame->width(), lb_frame->height())));
}
