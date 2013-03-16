#ifndef HTTP_SENDER_H
#define HTTP_SENDER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QUrl>
#include <cstdio>

class http_sender : public QObject
{
    Q_OBJECT
public:
    QNetworkAccessManager *network_manager;
public:
    http_sender();
    bool send_login_data(const QString &login_url, QByteArray &login_data);
public slots:

};

#endif // HTTP_SENDER_H
