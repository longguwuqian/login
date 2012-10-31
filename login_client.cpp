#include <QApplication>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QMessageBox>
#include <QLineEdit>
#include "login_client.h"

login_client::login_client(QObject *parent) :
    QObject(parent)
{
    this->wgt_login = new login_widget;
    this->camera_ctl = new camera_controller(0);
    this->tcp_sdr = new tcp_sender();
    this->img_tmp_file = NULL;

    connect(this->camera_ctl->cpt_thread, SIGNAL(new_frame(QImage *, QMutex *, QWaitCondition *, volatile bool *)), this->wgt_login->wgt_camera, SLOT(update_frame(QImage *, QMutex *, QWaitCondition *, volatile bool *)));
    connect(this->wgt_login->btn_login, SIGNAL(clicked()), this, SLOT(login()));
    connect(this->tcp_sdr, SIGNAL(receive_status_done()), this, SLOT(login_process()));
}

login_client::~login_client()
{
    delete this->wgt_login;
    delete this->tcp_sdr;
    this->camera_ctl->stop_capture_thread();
    if (camera_ctl != NULL) delete camera_ctl;
    if (this->img_tmp_file != NULL) delete this->img_tmp_file;
}

void login_client::start()
{
    this->camera_ctl->start_capture_thread();
    this->wgt_login->setStyleSheet("QWidget {background-color: beige;}QLabel, QAbstractButton {font: bold;}QPushButton {background-color: palegoldenrod; border-width: 2px; border-color: darkkhaki; border-style: solid; border-radius: 5; padding: 3px; min-width: 9ex; min-height: 2.5ex; } QPushButton:hover {background-color: khaki; }QPushButton:pressed { padding-left: 5px; padding-top: 5px; background-color: #d0d67c;}");
    /*居中放置*/
    this->wgt_login->move((QApplication::desktop()->width() - this->wgt_login->width()) / 2, (QApplication::desktop()->height() - this->wgt_login->height()) / 2);
    this->wgt_login->show();
}
void login_client::send_img()
{
    this->camera_ctl->stop_capture_thread();

    if (this->img_tmp_file != NULL) delete this->img_tmp_file;
    this->img_tmp_file = new QTemporaryFile();
    if (this->img_tmp_file->open()) {
        this->camera_ctl->cpt_thread->get_frame().save(this->img_tmp_file->fileName(), "png");
    }
    this->tcp_sdr->set_img_file(this->img_tmp_file);
    this->tcp_sdr->send_img();
    this->camera_ctl->start_capture_thread();
}

void login_client::login()
{
    if (this->wgt_login->le_username->text().length() == 0) QMessageBox::warning(this->wgt_login, tr("warning"), tr("user name is empty!"), QMessageBox::Ok);
    else {
        this->username = this->wgt_login->le_username->text();
        this->tcp_sdr->send_username(this->username);
        this->send_img();
    }
}
//bool login_client::get_login_status()
//{
//    bool status = true;
//    if (config_manager::get_instance().get_login_url().isNull()) return false;
//    if (config_manager::get_instance().is_use_default_browser()) {
//        status = QDesktopServices::openUrl(QUrl(config_manager::get_instance().get_login_url()));
//    } else {
//        QStringList arg_list;
//        arg_list.append(config_manager::get_instance().get_login_url());
//        this->proc_browser = new QProcess;
//        this->proc_browser->start(config_manager::get_instance().get_browser_path(), arg_list, QIODevice::ReadWrite);
//    }
//    return status;
//}
void login_client::login_process()
{
    if (config_manager::get_instance().is_loggedin == false) {
        QMessageBox::warning(this->wgt_login, tr("warning"), tr("you are not logged in"), QMessageBox::Ok);
    } else {
        QMessageBox::information(this->wgt_login, tr("welcome"), "username:"+this->username+"s_code:"+config_manager::get_instance().s_code, QMessageBox::Ok);
    }
}
