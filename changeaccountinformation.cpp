#include "changeaccountinformation.h"
#include "ui_changeaccountinformation.h"
#include <QMessageBox>
ChangeAccountInformation::ChangeAccountInformation(Client* c,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChangeAccountInformation)
{
    ui->setupUi(this);
    player = c;
    connect(player,SIGNAL(Order(QString)),this,SLOT(GetOrderOfClient(QString)));
}

ChangeAccountInformation::~ChangeAccountInformation()
{
    delete ui;
}

void ChangeAccountInformation::on_buttonBox_accepted()
{
    if(!ui->email->text().contains("@") || !ui->email->text().contains(".com")){
        QMessageBox::critical(nullptr, "Change Account Information ERROR", "Invalid Email");
    }
    if(ui->phone->text().length() != 11){
        QMessageBox::critical(nullptr, "Change Account Information ERROR", "Invalid Phone Number");
    }
    if(ui->pass->text().length() < 8){
        QMessageBox::critical(nullptr, "Change Account Information ERROR", "Password Should Have At least 8 Characters");
    }
    else if (ui->email->text().contains("@") && ui->email->text().contains(".com") && ui->phone->text().length() == 11 && ui->pass->text().length() >=8){
        player->ChangeInformation(player->Username,ui->username->text(),ui->pass->text(),ui->name->text(),ui->phone->text(),ui->email->text());
    }
}


void ChangeAccountInformation::on_buttonBox_rejected()
{
    this->close();
}

void ChangeAccountInformation::GetOrderOfClient(QString order)
{
    QStringList parts = order.split("|");
    if(parts[0] == "InformationChanged"){
        QMessageBox::critical(nullptr, "Change Account Information", "User Information Edited Succecfully");
        this->close();
    }else if (order == "ChangeInformationError"){
        QMessageBox::critical(nullptr, "Change Account Information ERROR", "The New Username Already Exist");
    }
}

