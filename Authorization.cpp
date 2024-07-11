#include "Authorization.h"
#include "forgotpassword.h"
#include "signupdialog.h"
#include "Menu.h"
#include "ui_Authorization.h"
Authorization::Authorization(Client* c,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Authorization)
{
    ui->setupUi(this);
    player = c;
    connect(player,SIGNAL(Order(QString)),this,SLOT(getOrderOfClient(QString)));
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_pushButton_2_clicked()
{
    SignupDialog* signupPlants = new SignupDialog(this);
    connect(signupPlants,SIGNAL(signupInformationEntered(QString,QString,QString,QString,QString)),this,SLOT(getEnteredData(QString,QString,QString,QString,QString)));
    connect(player,SIGNAL(Order(QString)),signupPlants,SLOT(getOrderOfClient(QString)));
    signupPlants->show();
}

void Authorization::getEnteredData(QString username,QString password,QString name,QString phone,QString address)
{
    player->registerUser(username,password,name,phone,address);
}


void Authorization::on_pushButton_clicked()
{
    player->loginUser(ui->lineEdit->text(),ui->lineEdit_2->text());
}


void Authorization::on_pushButton_3_clicked()
{
    ForgotPassword* forgot = new ForgotPassword(this);
    connect(forgot,SIGNAL(changeForgotedPassword(QString,QString)),this,SLOT(resetPassword(QString,QString)));
    connect(player,SIGNAL(Order(QString)),forgot,SLOT(getOrderOfClient(QString)));
    forgot->show();
}

void Authorization::getOrderOfClient(QString order)
{
if (order == "LoginError"){
        QMessageBox::critical(nullptr, "Login ERROR", "Username Or Password is Wrong");
    }
else{
    QStringList orderParts = order.split("|");
    if(orderParts[0] == "Loggedin"){
    Menu *menu = new Menu(player);
    connect(menu,SIGNAL(Back()),this,SLOT(getBackToTheAuthorizationPage()));
    menu->show();
    this->hide();
    }
}
}

void Authorization::getBackToTheAuthorizationPage()
{
    player->username="";
    this->show();
}

void Authorization::resetPassword(QString phone, QString newpass){
    player->resetPassword(phone,newpass);
}
