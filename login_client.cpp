#include <QApplication>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QMessageBox>
#include <QLineEdit>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include "login_client.h"

using namespace cv;

login_client::login_client(QObject *parent) :
    QObject(parent)
{
    this->wgt_login = new login_widget;
    this->img_tmp_file = NULL;
    config_manager::get_instance().set_login_url("http://192.168.64.51:8080/BMS/da_login.jsp");

    connect(this->wgt_login->btn_login, SIGNAL(clicked()), this, SLOT(login()));
    connect(this->httpsdr.network_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(login_finished(QNetworkReply*)));
}

login_client::~login_client()
{
    this->wgt_login->wgt_camera->stop_capture_thread();
    delete this->wgt_login;
    if (this->img_tmp_file != NULL) delete this->img_tmp_file;
}

void login_client::login_finished(QNetworkReply *reply)
{
    QString login_status(reply->readAll().data());
    login_status = login_status.simplified();
    if (login_status.length() < 3)
        QMessageBox::warning(0, tr("warning"), login_status, QMessageBox::Ok);
    else {
        QString scode = login_status;

        if (config_manager::get_instance().get_login_url().isNull()) return;
        if (config_manager::get_instance().is_use_default_browser()) {
            QDesktopServices::openUrl(QUrl(config_manager::get_instance().get_login_url() + "?scode=" + scode));
        } else {
            QStringList arg_list;
            arg_list.append(config_manager::get_instance().get_login_url() + "?scode=" + scode);
            this->proc_browser = new QProcess;
            this->proc_browser->start(config_manager::get_instance().get_browser_path(), arg_list, QIODevice::ReadWrite);
        }
    }
}

void login_client::start()
{
    this->wgt_login->wgt_camera->start_capture_thread();
    this->wgt_login->setStyleSheet("QWidget {background-color: beige;}QLabel, QAbstractButton {font: bold;}QPushButton {background-color: palegoldenrod; border-width: 2px; border-color: darkkhaki; border-style: solid; border-radius: 5; padding: 3px; min-width: 9ex; min-height: 2.5ex; } QPushButton:hover {background-color: khaki; }QPushButton:pressed { padding-left: 5px; padding-top: 5px; background-color: #d0d67c;}");
    /*居中放置*/
    this->wgt_login->move((QApplication::desktop()->width() - this->wgt_login->width()) / 2, (QApplication::desktop()->height() - this->wgt_login->height()) / 2);
    this->wgt_login->show();
}
void login_client::send_img()
{
    if (this->img_tmp_file != NULL) delete this->img_tmp_file;
    this->img_tmp_file = new QTemporaryFile();
    if (this->img_tmp_file->open()) {
        this->wgt_login->wgt_camera->get_frame_qimage().save(this->img_tmp_file->fileName(), "png");
    }
}

void login_client::login()
{
    if (this->wgt_login->le_username->text().length() == 0)
        QMessageBox::warning(this->wgt_login, tr("warning"), tr("user name is empty!"), QMessageBox::Ok);
    else {

        IplImage *gray_img, *img;
        img = this->wgt_login->wgt_camera->get_frame_iplimage();
        gray_img = cvCreateImage(cvSize(img->width,img->height), IPL_DEPTH_8U, 1);
        cvCvtColor(img, gray_img, CV_RGB2GRAY);

        this->fd.set_input_image(gray_img);
        if (!this->fd.get_face_parameters()) {
            fprintf(stderr, "WRONG!!!");
            return;
        }
        this->username = this->wgt_login->le_username->text();
        Mat imgdata = Mat(this->fd.get_face_img(), true);
        QByteArray qba = QByteArray("id=");
        qba.append(this->username);
        qba.append("&img=");
        qba.append(QByteArray((const char *)imgdata.data, imgdata.rows * imgdata.cols).toBase64());
        this->httpsdr.send_login_data("http://192.168.64.51:8080/BMS/da_face_login.jsp", qba);
    }
}

void login_client::login_process()
{
    if (config_manager::get_instance().is_loggedin == false) {
        QMessageBox::warning(this->wgt_login, tr("warning"), tr("you are not logged in"), QMessageBox::Ok);
    } else {
        QMessageBox::information(this->wgt_login, tr("welcome"), "username:"+this->username+"s_code:"+config_manager::get_instance().s_code, QMessageBox::Ok);
    }
}
