#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDateTime>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>

class Server : public QTcpServer
{
public:
    Server();
    QTcpSocket *socket;

private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    void SendToClient();
    int generateNumber();

public slots:
    void incomingConnection(qintptr SocketDescriptor);
    void slotreadyRead();

private slots:
    void sendData();
};

#endif // SERVER_H
