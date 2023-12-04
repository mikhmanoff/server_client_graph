#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>

#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTcpSocket *socket;
    QByteArray Data;
    void sendToServer();

    double time;
    QTimer *myTimer;

    QCustomPlot *customPlot;
    QVector<double> xData, yData;

public slots:
    void slotReadyRead();
};
#endif // MAINWINDOW_H
