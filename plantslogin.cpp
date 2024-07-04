#include "plantslogin.h"
#include "forgotpassword.h"
#include "signupdialog.h"
#include "ui_plantslogin.h"

PlantsLogin::PlantsLogin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlantsLogin)
{
    ui->setupUi(this);
    plants.connectToServer("127.0.0.1",12345);
}

PlantsLogin::~PlantsLogin()
{
    delete ui;
}

void PlantsLogin::on_pushButton_2_clicked()
{
    SignupDialog* signupPlants = new SignupDialog(this);
    connect(signupPlants,SIGNAL(SignupInformation_Entered(QString,QString,QString,QString,QString)),this,SLOT(Get_Entered_Information(QString,QString,QString,QString,QString)));
    signupPlants->show();
}

void PlantsLogin::Get_Entered_Data(QString username,QString password,QString name,QString phone,QString address)
{
    plants.registerUser(username,password,name,phone,address);
}


void PlantsLogin::on_pushButton_clicked()
{
    plants.loginUser(ui->lineEdit->text(),ui->lineEdit_2->text());
}


void PlantsLogin::on_pushButton_3_clicked()
{
    ForgotPassword* forgot = new ForgotPassword(this);
    connect(forgot,SIGNAL(ChangeForgotedPassword(QString,QString)),this,SLOT(Resetpassword(QString,QString)));
    forgot->show();
}

void PlantsLogin::Resetpassword(QString phone, QString newpass){
    plants.resetPassword(phone,newpass);
}
