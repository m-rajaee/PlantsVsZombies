#include "mainwindow.h"
#include "signupdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);

    //socket->connectToHost("server_ip",8080);
    socket->connectToHost("127.0.0.1",12345);

    if(socket->waitForConnected())
        ui->statusBar->showMessage("Connected to Server");
    else{
        QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    SignupDialog* signup = new SignupDialog(this);
    connect(signup,SIGNAL(SignupInformation_Entered(QString,QString,QString,QString,QString)),this,SLOT(Get_Entered_Information(QString,QString,QString,QString,QString)));
    signup->show();
}

void MainWindow::Get_Entered_Information(QString Name, QString Username, QString PhoneNumber, QString Email, QString Password)
{
    //Do The Things With Name , Username & ...
}


void MainWindow::on_pushButton_clicked()
{

}

