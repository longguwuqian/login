#ifndef TCP_SENDER_H
#define TCP_SENDER_H

#include <QtNetwork>
#include <QFile>

//const QString HOST_ADDR = "172.31.33.4";
const QString HOST_ADDR = "127.0.0.1";
const int HOST_PORT = 8888;

class tcp_sender : public QObject
{
    Q_OBJECT
public:
    tcp_sender();
    void send(QTemporaryFile *file);
private:
    QTcpSocket *tcp_client;
    QTemporaryFile *local_file;
    qint64 total_bytes;
    qint64 bytes_written;
    qint64 bytes_to_write;
    qint64 load_size;
    QByteArray out_block;
    QString file_path;
private slots:
    void start_transfer();//
    void display_error(QAbstractSocket::SocketError socket_error);
    void update_client_progress(qint64 num_bytes);
};

#endif // TCP_SENDER_H
