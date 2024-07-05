#include "zombiesmenu.h"
#include "ui_zombiesmenu.h"
#include "changeaccountinformation.h"
#include <QMessageBox>
ZombiesMenu::ZombiesMenu(Client* c,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ZombiesMenu)
{
    ui->setupUi(this);
    zombies = c;
    connect(zombies,SIGNAL(Order(QString)),this,SLOT(GetOrderOfClient(QString)));
}

ZombiesMenu::~ZombiesMenu()
{
    delete ui;
}

void ZombiesMenu::GetOrderOfClient(QString order)
{
    if (order == "Loggedin"){
        this->hide();
        //Open Menu
    }else if (order == "LoginError"){
        QMessageBox::critical(nullptr, "Login ERROR", "Username Or Password is Wrong");
    }else if (order == ""){

    }
}

void ZombiesMenu::on_pushButton_4_clicked()
{
    emit Back();
}


void ZombiesMenu::on_pushButton_clicked()
{

}

