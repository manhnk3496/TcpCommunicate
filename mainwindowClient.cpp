#include "mainwindow.h"
#include "ui_mainwindow.h"

static const int DEFAULT_PORT = 6789;
int port;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    port = DEFAULT_PORT;
    socket = new QTcpSocket(this);
    buffer = new QBuffer(this);
    buffer->open(QIODevice::ReadWrite);
    ui->textEditContent->setEnabled(false);
    ui->pushButtonDisconnect->setEnabled(false);

    connect(ui->pushButtonConnect,SIGNAL(clicked()),this,SLOT(setConnected()));
    connect(ui->pushButtonDisconnect,SIGNAL(clicked()),this,SLOT(setDisconnected()));
    connect(ui->lineEditChat,SIGNAL(returnPressed()),this,SLOT(sendMessage()));
    connect(ui->pushButtonSend,SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    setDisconnected();//at first, disConnection
}

/*.....................................................
 ......................................................*/
void MainWindow::setConnected(){
    socket->connectToHost("localhost",port);
    ui->pushButtonConnect->setEnabled(false);
    ui->pushButtonDisconnect->setEnabled(true);
    ui->labelCommunicate->setText("Communicate: Connect success...");
}

void MainWindow::setDisconnected(){
    socket->disconnectFromHost();
    ui->pushButtonConnect->setEnabled(true);
    ui->pushButtonDisconnect->setEnabled(false);
    ui->labelCommunicate->setText("Communicate: Stop connect...");
}

void MainWindow::sendMessage(){
    bool b = socket->write(ui->lineEditChat->text().toLatin1());
    ui->lineEditChat->clear();
    if (b){
        ui->labelCommunicate->setText("Communicate: Send success...");
    }
}

void MainWindow::receiveMessage(){
    ui->textEditContent->append("Server: "+socket->readAll());
}

MainWindow::~MainWindow()
{
    delete ui;
}
