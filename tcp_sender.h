#ifndef TCP_SENDER_H
#define TCP_SENDER_H

#include <QtNetwork>
#include <QFile>
#include <QString>

//const QString HOST_ADDR = "172.31.33.4";
const QString HOST_ADDR = "127.0.0.1";
const int HOST_PORT = 8888;

class tcp_sender : public QObject
{
    Q_OBJECT
public:
    tcp_sender();
    void set_img_file(QTemporaryFile *file);
    void send_username(QString &uname);
    void send_img();

private:
    QTcpSocket *client_socket;
    QTemporaryFile *local_file;
    qint64 total_bytes;
    qint64 bytes_written;
    qint64 bytes_to_write;
    qint64 load_size;
    QByteArray out_block;
    QString file_path;

    QString username;
    void confirm_username(QString &uname);
signals:
    void receive_status_done();
private slots:
    void start_transfer();//
    void display_error(QAbstractSocket::SocketError socket_error);
    void update_client_progress(qint64 num_bytes);
    void receive_status();


    void connected_to_host();
};

#endif // TCP_SENDER_H
