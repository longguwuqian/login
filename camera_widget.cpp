#include <QtGui>
#include <QDebug>
#include "camera_widget.h"

camera_widget::camera_widget(QWidget *parent, int max_width, int max_height, int min_width, int min_height)
    : QWidget(parent)
{
    this->img_tmp_file = NULL;
    lb_frame = new QLabel(this);
    this->lb_frame->setMinimumSize(640, 480);
    this->setMinimumSize(640, 480);

    this->camera_ctlr = new camera_controller(0);
    this->camera_ctlr->start_capture_thread();

    this->my_tcp_sender = new tcp_sender();

    connect(this->camera_ctlr->cpt_thread, SIGNAL(new_frame(QImage *, QMutex *, QWaitCondition *, volatile bool *)), this, SLOT(update_frame(QImage *, QMutex *, QWaitCondition *, volatile bool *)));
}

camera_widget::~camera_widget(void)
{
    if (this->img_tmp_file != NULL) delete this->img_tmp_file;
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

void camera_widget::save_image_tmp()
{
    this->camera_ctlr->stop_capture_thread();

    if (this->img_tmp_file != NULL) delete this->img_tmp_file;
    this->img_tmp_file = new QTemporaryFile();
    if (this->img_tmp_file->open()) {
        //this->img_tmp_file->close();
        if (this->camera_ctlr->cpt_thread->get_frame().save(this->img_tmp_file->fileName(), "png")) qDebug() << "saaaaaaaaaaa";
        qDebug() << this->img_tmp_file->fileName();
    }
    this->my_tcp_sender->send(this->img_tmp_file);
    this->camera_ctlr->start_capture_thread();
}

void camera_widget::update_frame(QImage *img_frame, QMutex *update_done_mutex, QWaitCondition *update_done_condition, volatile bool *update_done)
{
    update_done_mutex->lock();

    this->lb_frame->setPixmap(QPixmap::fromImage(*img_frame));
    *update_done = true;
    update_done_condition->wakeAll();
    update_done_mutex->unlock();
}
