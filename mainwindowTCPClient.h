#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QBuffer>

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
    void setConnected();
    void setDisconnected();
    void sendMessage();
    void receiveMessage();

private:
    QTcpSocket *socket;
    QBuffer *buffer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
