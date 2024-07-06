#include "Menu.h"
#include "ui_Menu.h"
#include "changeaccountinformation.h"
#include <QMessageBox>
#include "showhistory.h"
Menu::Menu(Client* c,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    player = c;
    connect(player,SIGNAL(Order(QString)),this,SLOT(GetOrderOfClient(QString)));
    ui->label->setText("Welcome To The Game, "+player->Username);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::GetOrderOfClient(QString order)
{
    if (order == "ChangeInformationError"){

    }else if (order == "InformationChanged"){
        QMessageBox::critical(nullptr, "Login ERROR", "Username Or Password is Wrong");
    }else if (order == ""){

    }
}

void Menu::on_pushButton_4_clicked()
{
    emit Back();
    this->close();
}


void Menu::on_pushButton_clicked()
{

}


void Menu::on_pushButton_2_clicked()
{
    ChangeAccountInformation* changeaccountinformation = new ChangeAccountInformation(player);
    changeaccountinformation->show();
}


void Menu::on_pushButton_3_clicked()
{
    ShowHistory* showhistroy = new ShowHistory(player);
    showhistroy->show();
}

