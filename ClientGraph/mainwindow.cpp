#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::deleteLater);

    QString serverAddress = "127.0.0.1"; // IP адрес сервера
    quint16 serverPort = 2323; // Порт сервера

    // Подключение к серверу
    socket->connectToHost(serverAddress, serverPort);

    // Проверка успешности подключения
    if (socket->waitForConnected()) {
        qDebug() << "Connected to the server";
        slotReadyRead();
    } else {
        qDebug() << "Failed to connect to the server";
    }

    customPlot = new QCustomPlot(this);
    setCentralWidget(customPlot);

    customPlot->setFixedSize(800, 400);

    customPlot->addGraph();
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Value");

    myTimer = new QTimer(this);
    connect(myTimer, &QTimer::timeout, this, &MainWindow::sendToServer);
    myTimer->start(1000);
}

MainWindow::~MainWindow()
{
    delete myTimer;
    delete customPlot;
}

void MainWindow::slotReadyRead() {
    QByteArray jsonData = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (!doc.isNull() && doc.isObject()) {
        QJsonObject jsonObj = doc.object();
        int number = jsonObj["number"].toInt();

        xData.append(time);
        yData.append(number);

        customPlot->graph(0)->setData(xData, yData);
        customPlot->rescaleAxes();
        customPlot->replot();

        time += 1;

        qDebug() << number << '\n';
        // Обновление графика
    } else {
        qDebug() << "error read daata" << '\n';
    }

}

void MainWindow::sendToServer() {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    socket->write(Data);
}
