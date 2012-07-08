#include <QtGui>
#include <QDebug>
#include "camera_widget.h"

camera_widget::camera_widget(QWidget *parent, int max_width, int max_height, int min_width, int min_height)
    : QWidget(parent)
{
    lb_frame = new QLabel(this);
    this->lb_frame->setMinimumSize(640, 480);
    this->setMinimumSize(640, 480);

    this->camera_ctlr = new camera_controller(0);
    this->camera_ctlr->start_capture_thread();
    this->img_border = new QImage("border.png");
    assert(!this->img_border->isNull());

    connect(this->camera_ctlr->cpt_thread, SIGNAL(new_frame(QImage *, QMutex *)), this, SLOT(update_frame(QImage *, QMutex *)));
}

camera_widget::~camera_widget(void)
{
    this->camera_ctlr->stop_capture_thread();
    if (camera_ctlr != NULL) delete camera_ctlr;
}

void camera_widget::save_image()
{
    this->camera_ctlr->stop_capture_thread();
    QString path = QFileDialog::getSaveFileName((QWidget *)this->parent(), tr("save file dialog"), ".", tr("*.png"));
    if (path != NULL) this->camera_ctlr->cpt_thread->get_frame().save(path);
    this->camera_ctlr->start_capture_thread();
}

void camera_widget::update_frame(QImage *img_frame, QMutex *update_done_mutex)
{
//    update_done_mutex->lock();
    QPainter *_img_painter = new QPainter(img_frame);
    _img_painter->setOpacity(0.4);
    _img_painter->drawImage(img_frame->width() / 2 - 170, img_frame->height() / 2 - 190, *this->img_border);
    _img_painter->end();
    this->lb_frame->setPixmap(QPixmap::fromImage(*img_frame));
    update_done_mutex->unlock();
}
