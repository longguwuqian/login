#include "http_sender.h"
#include <QMessageBox>
#include <QDebug>

http_sender::http_sender()
{
    this->network_manager = new QNetworkAccessManager(this);
}



bool http_sender::send_login_data(const QString &login_url, QByteArray &login_data)
{
    static QNetworkRequest request;
    QNetworkReply *reply;

    request.setUrl(QUrl(login_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader, login_data.length());
    reply = this->network_manager->post(request, login_data);

    return true;
}

