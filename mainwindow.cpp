#include "mainwindow.h"
#include "signupdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

