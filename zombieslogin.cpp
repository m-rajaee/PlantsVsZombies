#include "zombieslogin.h"
#include "signupdialog.h"
#include "ui_zombieslogin.h"
#include "forgotpassword.h"
#include "zombiesmenu.h"
ZombiesLogin::ZombiesLogin(Client* c,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ZombiesLogin)
{
    ui->setupUi(this);
    zombies = c;
    connect(zombies,SIGNAL(Order(QString)),this,SLOT(GetOrderOfClient(QString)));
}

ZombiesLogin::~ZombiesLogin()
{
    delete ui;
}

void ZombiesLogin::on_pushButton_2_clicked()
{
    SignupDialog* signupzombies = new SignupDialog(this);
    connect(signupzombies,SIGNAL(SignupInformation_Entered(QString,QString,QString,QString,QString)),this,SLOT(Get_Entered_Information(QString,QString,QString,QString,QString)));
    connect(zombies,SIGNAL(Order(QString)),signupzombies,SLOT(GetOrderOfClient(QString)));
    signupzombies->show();
}

void ZombiesLogin::Get_Entered_Data(QString username,QString password,QString name,QString phone,QString address)
{
    zombies->registerUser(username,password,name,phone,address);
}


void ZombiesLogin::on_pushButton_clicked()
{
    zombies->loginUser(ui->lineEdit->text(),ui->lineEdit_2->text());
}


void ZombiesLogin::on_pushButton_3_clicked()
{
    ForgotPassword* forgot = new ForgotPassword(this);
    connect(forgot,SIGNAL(ChangeForgotedPassword(QString,QString)),this,SLOT(Resetpassword(QString,QString)));
    connect(zombies,SIGNAL(Order(QString)),forgot,SLOT(GetOrderOfClient(QString)));
    forgot->show();
}

void ZombiesLogin::GetOrderOfClient(QString order)
{
    if (order == "Loggedin"){
        ZombiesMenu *zombiesmenu = new ZombiesMenu(zombies);
        connect(zombiesmenu,SIGNAL(Back()),this,SLOT(GetBack()));
        zombiesmenu->show();
        this->hide();
    }else if (order == "LoginError"){
        QMessageBox::critical(nullptr, "Login ERROR", "Username Or Password is Wrong");
    }
}

void ZombiesLogin::GetBack()
{
    this->show();
}

void ZombiesLogin::Resetpassword(QString phone, QString newpass){
    zombies->resetPassword(phone,newpass);
}
