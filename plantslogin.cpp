#include "plantslogin.h"
#include "forgotpassword.h"
#include "signupdialog.h"
#include "plantsmenu.h"
#include "ui_plantslogin.h"

PlantsLogin::PlantsLogin(Client* c,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlantsLogin)
{
    ui->setupUi(this);
    plants = c;
    connect(plants,SIGNAL(Order(QString)),this,SLOT(GetOrderOfClient(QString)));
}

PlantsLogin::~PlantsLogin()
{
    delete ui;
}

void PlantsLogin::on_pushButton_2_clicked()
{
    SignupDialog* signupPlants = new SignupDialog(this);
    connect(signupPlants,SIGNAL(SignupInformation_Entered(QString,QString,QString,QString,QString)),this,SLOT(Get_Entered_Data(QString,QString,QString,QString,QString)));
    connect(plants,SIGNAL(Order(QString)),signupPlants,SLOT(GetOrderOfClient(QString)));
    signupPlants->show();
}

void PlantsLogin::Get_Entered_Data(QString username,QString password,QString name,QString phone,QString address)
{
    plants->registerUser(username,password,name,phone,address);
}


void PlantsLogin::on_pushButton_clicked()
{
    plants->loginUser(ui->lineEdit->text(),ui->lineEdit_2->text());
}


void PlantsLogin::on_pushButton_3_clicked()
{
    ForgotPassword* forgot = new ForgotPassword(this);
    connect(forgot,SIGNAL(ChangeForgotedPassword(QString,QString)),this,SLOT(Resetpassword(QString,QString)));
    connect(plants,SIGNAL(Order(QString)),forgot,SLOT(GetOrderOfClient(QString)));
    forgot->show();
}

void PlantsLogin::GetOrderOfClient(QString order)
{
if (order == "LoginError"){
        QMessageBox::critical(nullptr, "Login ERROR", "Username Or Password is Wrong");
    }
else{
    QStringList parts = order.split("|");
    if(parts[0] == "Loggedin"){
    PlantsMenu *plantsmenu = new PlantsMenu(plants);
    connect(plantsmenu,SIGNAL(Back()),this,SLOT(GetBack()));
    plantsmenu->show();
    this->hide();
    }
}
}

void PlantsLogin::GetBack()
{
    this->show();
}

void PlantsLogin::Resetpassword(QString phone, QString newpass){
    plants->resetPassword(phone,newpass);
}
