#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QHash>
#include <QList>

class QBuffer;
class QTcpSocket;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //function create autumatic
    void on_pushButtonListen_clicked();
    void on_pushButtonSleep_clicked();
    //function create by handle
    void addConnection();
    void ReceiveMessage();
    void removeConnect();
    void sendMessage();

private:
    QBuffer *buffer;
    QTcpSocket* socket;
    QTcpServer *server;
    QList<QTcpSocket*> connections;
    QHash<QTcpSocket*, QBuffer*> buffers;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
