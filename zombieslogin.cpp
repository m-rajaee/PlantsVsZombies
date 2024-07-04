#include "zombieslogin.h"
#include "signupdialog.h"
#include "ui_zombieslogin.h"
#include "forgotpassword.h"
ZombiesLogin::ZombiesLogin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ZombiesLogin)
{
    ui->setupUi(this);
    zombies.connectToServer("127.0.0.1",12345);
}

ZombiesLogin::~ZombiesLogin()
{
    delete ui;
}

void ZombiesLogin::on_pushButton_2_clicked()
{
    SignupDialog* signupzombies = new SignupDialog(this);
    connect(signupzombies,SIGNAL(SignupInformation_Entered(QString,QString,QString,QString,QString)),this,SLOT(Get_Entered_Information(QString,QString,QString,QString,QString)));
    signupzombies->show();
}

void ZombiesLogin::Get_Entered_Data(QString username,QString password,QString name,QString phone,QString address)
{
    zombies.registerUser(username,password,name,phone,address);
}


void ZombiesLogin::on_pushButton_clicked()
{
    zombies.loginUser(ui->lineEdit->text(),ui->lineEdit_2->text());
}


void ZombiesLogin::on_pushButton_3_clicked()
{
    ForgotPassword* forgot = new ForgotPassword(this);
    connect(forgot,SIGNAL(ChangeForgotedPassword(QString,QString)),this,SLOT(Resetpassword(QString,QString)));
    forgot->show();
}

void ZombiesLogin::Resetpassword(QString phone, QString newpass){
    zombies.resetPassword(phone,newpass);
}
