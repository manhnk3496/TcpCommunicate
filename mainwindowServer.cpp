#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>
#include <QTcpSocket>

static const int DEFAULT_PORT = 6789;
int port;
QHostAddress server_add;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer();
    //event appear newconnection
    connect(server,SIGNAL(newConnection()),this,SLOT(addConnection()));
    connect(ui->lineEditChat,SIGNAL(returnPressed()),this,SLOT(sendMessage()));
    connect(ui->pushButtonSend,SIGNAL(clicked()),this,SLOT(sendMessage()));
    server_add = QHostAddress::LocalHost; //get address host
    port = DEFAULT_PORT;
    ui->textEditContent->setEnabled(false);
    ui->labelCommunicate->setText("Communicate: server sleep..");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonListen_clicked()
{
    server->listen(server_add, port);
    if(server->isListening())
    {
        ui->labelCommunicate->setText("Start listen...");
        ui->pushButtonListen->setEnabled(false);
        ui->pushButtonSleep->setEnabled(true);
    }
    else
    {
        ui->labelCommunicate->setText("Warn: Now, server not listen!!!");
        ui->labelCommunicate->setText(ui->labelCommunicate->text()+" Please: inspect");
    }
}

void MainWindow::on_pushButtonSleep_clicked()
{
    if(server->isListening())
    {
        server->close();
        ui->pushButtonListen->setEnabled(true);
        ui->pushButtonSleep->setEnabled(false);
    }
}

/*.................................................
 handle functions with connect and message
 Add connection in socket
 Remove connection from socket
 Send a message
 receive a message
  .................................................*/

void MainWindow::addConnection(){
    //add a new connect
    socket =  server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReceiveMessage()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(removeConnect()));
    socket->write("Connection!");
}

void MainWindow::sendMessage()
{
    socket->write(ui->lineEditChat->text().toLatin1());
    ui->lineEditChat->clear();
    ui->labelCommunicate->setText("Send success!!!");
}

void MainWindow::ReceiveMessage(){
    ui->textEditContent->append("Client: "+socket->readAll());
}

void MainWindow::removeConnect()
{
    server->close();
    ui->labelCommunicate->setText("Client is Disconnect, Server is close!");
    ui->pushButtonListen->setEnabled(true);
    ui->pushButtonSleep->setEnabled(false);
}
