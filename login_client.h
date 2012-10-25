#ifndef LOGIN_CLIENT_H
#define LOGIN_CLIENT_H

#include <QObject>
#include <QTemporaryFile>
#include <QPushButton>
#include "ui/login_widget.h"
#include "config_manager.h"
#include "camera_controller.h"
#include "tcp_sender.h"

class login_client : public QObject
{
    Q_OBJECT
private:
    login_widget *wgt_login;
    camera_controller *camera_ctl;
    tcp_sender *tcp_sdr;
    QTemporaryFile *img_tmp_file;
    QProcess *proc_browser;

    void send_img();
public:
    explicit login_client(QObject *parent = 0);
    ~login_client();
    void start();
signals:
    
public slots:
    bool login();
};

#endif // LOGIN_CLIENT_H
