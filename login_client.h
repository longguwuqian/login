#ifndef LOGIN_CLIENT_H
#define LOGIN_CLIENT_H

#include <QObject>
#include <QTemporaryFile>
#include <QPushButton>
#include <QString>
#include <QProcess>
#include "ui/login_widget.h"
#include "config_manager.h"
#include "http_sender.h"

#include "face_detector/face_detector.h"

class login_client : public QObject
{
    Q_OBJECT
private:
    login_widget *wgt_login;
    QTemporaryFile *img_tmp_file;
    QProcess *proc_browser;
    QString username;
    http_sender httpsdr;

    face_detector fd;

    void send_img();
    void send_PCA_coeff();
public:
    explicit login_client(QObject *parent = 0);
    ~login_client();
    void start();
signals:
    
public slots:
    void login();
    void login_process();
    void login_finished(QNetworkReply* reply);

};

#endif // LOGIN_CLIENT_H
