#include "tcp_sender.h"
#include "config_manager.h"

tcp_sender::tcp_sender()
{
    this->load_size = 4 * 1024;
    this->local_file = NULL;
    this->total_bytes = 0;
    this->bytes_written = 0;
    this->bytes_to_write = 0;
    this->client_socket = new QTcpSocket(this);

    connect(client_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(update_client_progress(qint64)));
    connect(client_socket, SIGNAL(connected()), this, SLOT(connected_to_host()));
    connect(client_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(display_error(QAbstractSocket::SocketError)));
    connect(client_socket, SIGNAL(readyRead()), this, SLOT(get_url()));

    this->client_socket->connectToHost(HOST_ADDR, HOST_PORT);
}
void tcp_sender::connected_to_host()
{
    qDebug() << "connected to host.";
}

void tcp_sender::get_url()
{
    qDebug() << "in get_url()";
    QString *url;
    url = new QString(this->client_socket->readLine());
    qDebug() << *url;
    config_manager::get_instance().set_login_url(*url);
    emit get_url_done();
    delete url;
}

void tcp_sender::display_error(QAbstractSocket::SocketError socket_error)
{
    qDebug() << "ooooooooooooooooooooooooo" << client_socket->errorString();
    client_socket->close();
}

void tcp_sender::send(QTemporaryFile *file)
{
    this->local_file = file;
    this->bytes_written = 0;
    this->total_bytes = 0;
    this->bytes_written = 0;
    this->bytes_to_write = 0;
    start_transfer();
}

void tcp_sender::start_transfer()
{
    qDebug() << "in start_transfer";
    qDebug() << this->local_file->size();
    this->total_bytes = this->local_file->size();
    this->file_path = this->local_file->fileName();
    QDataStream send_out(&out_block, QIODevice::WriteOnly);
    QString file_name = this->file_path.right(this->file_path.size() - this->file_path.lastIndexOf('/') - 1);
    qDebug() << file_path;
    send_out << qint64(0) << qint64(0) << file_name;
    this->total_bytes += this->out_block.size();
    send_out.device()->seek(0);
    send_out << this->total_bytes << qint64(this->out_block.size() - sizeof(qint64) * 2);
    this->bytes_to_write = this->total_bytes - this->client_socket->write(this->out_block);
    this->out_block.resize(0);
}

void tcp_sender::update_client_progress(qint64 num_bytes) //更新进度条，实现文件的传送
{
    bytes_written += (int)num_bytes;
    //已经发送数据的大小
    if(bytes_to_write > 0) //如果已经发送了数据
    {
        out_block = local_file->read(qMin(bytes_to_write,load_size));
      //每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，
      //就发送剩余数据的大小
        bytes_to_write -= (int)client_socket->write(out_block);
       //发送完一次数据后还剩余数据的大小
        out_block.resize(0);
        //清空发送缓冲区
    }
    else
    {
        local_file->close(); //如果没有发送任何数据，则关闭文件
    }
    //更新进度条
    if(bytes_written == total_bytes) //发送完毕
    {
        local_file->close();
//        tcp_client->close();
    }
}