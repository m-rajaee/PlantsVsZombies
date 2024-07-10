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
    connect(player,SIGNAL(Order(QString)),this,SLOT(GetOrderOfClient(QString)));
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_pushButton_2_clicked()
{
    SignupDialog* signupPlants = new SignupDialog(this);
    connect(signupPlants,SIGNAL(SignupInformation_Entered(QString,QString,QString,QString,QString)),this,SLOT(Get_Entered_Data(QString,QString,QString,QString,QString)));
    connect(player,SIGNAL(Order(QString)),signupPlants,SLOT(GetOrderOfClient(QString)));
    signupPlants->show();
}

void Authorization::Get_Entered_Data(QString username,QString password,QString name,QString phone,QString address)
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
    connect(forgot,SIGNAL(ChangeForgotedPassword(QString,QString)),this,SLOT(Resetpassword(QString,QString)));
    connect(player,SIGNAL(Order(QString)),forgot,SLOT(GetOrderOfClient(QString)));
    forgot->show();
}

void Authorization::GetOrderOfClient(QString order)
{
if (order == "LoginError"){
        QMessageBox::critical(nullptr, "Login ERROR", "Username Or Password is Wrong");
    }
else{
    QStringList parts = order.split("|");
    if(parts[0] == "Loggedin"){
    Menu *menu = new Menu(player);
    connect(menu,SIGNAL(Back()),this,SLOT(GetBack()));
    menu->show();
    this->hide();
    }
}
}

void Authorization::GetBack()
{
    player->Username="";
    this->show();
}

void Authorization::Resetpassword(QString phone, QString newpass){
    player->resetPassword(phone,newpass);
}
