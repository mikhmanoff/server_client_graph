#include "server.h"

Server::Server()
{
    if (this->listen(QHostAddress::Any, 2323)) {
        qDebug() << "start";
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Server::SendToClient);
        timer->start(1000);
    } else {
        qDebug() << "listen";
    }
}

void Server::incomingConnection(qintptr SocketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);

    socket->setSocketDescriptor(SocketDescriptor);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    qDebug() << "client connected" << SocketDescriptor;
}

void Server::SendToClient() {
    Data.clear();
    int number = generateNumber();

    QJsonObject jsonData;

    jsonData["number"] = number;
    QByteArray data = QJsonDocument(jsonData).toJson();

    for (QTcpSocket *socket : this->findChildren<QTcpSocket*>()) {
        socket->write(data);
        qDebug() << data;
    }
}

int Server::generateNumber() {
    return rand() % 10000;
}
