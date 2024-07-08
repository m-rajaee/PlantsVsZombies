#include "Menu.h"
#include "ui_Menu.h"
#include "changeaccountinformation.h"
#include <QMessageBox>
#include "showhistory.h"
#include "letsplay.h"
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
    QStringList parts = order.split("|");
    if(parts[0] == "LetsPlay"){
        LetsPlay* letsplay = new LetsPlay(player,parts[1]);
        letsplay->show();
    }
    else if(order == "MatchStarted"){
        // start the game
    }
    else if(order == "MatchStartRefused"){
        QMessageBox::critical(nullptr, "Match Start ERROR", "Other Player Refused To Play");
    }
}

void Menu::on_pushButton_4_clicked()
{
    emit Back();
    this->close();
}


void Menu::on_pushButton_clicked()
{
    player->SendMessage("LetsPlay|"+player->Username);
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

