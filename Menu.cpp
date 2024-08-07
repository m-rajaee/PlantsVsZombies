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
    menuSound = new QSoundEffect();
    menuSound->setSource(QUrl::fromLocalFile(":/audio/Menu.wav"));
    menuSound->setVolume(0.4);
    menuSound->play();
    menuSound->setLoopCount(QSoundEffect::Infinite);
    ui->setupUi(this);
    player = c;
    connect(player,SIGNAL(Order(QString)),this,SLOT(getOrderOfClient(QString)));
    ui->label->setText("Welcome To The Game, "+player->username);
    connect(player,SIGNAL(matchFinished()),this,SLOT(matchFinished()));
}

Menu::~Menu()
{
    delete ui;
}

void Menu::getOrderOfClient(QString order)
{
    QStringList parts = order.split("|");
    if(parts[0] == "LetsPlay"){
        LetsPlay* letsplay = new LetsPlay(player,parts[1]);
        connect(letsplay,SIGNAL(matchStarted()),this,SLOT(gameStarted()));
        letsplay->show();
    }else if(parts[0] == "StartTheMatch"){
        menuSound->stop();
        this->close();
    }
    else if(order == "MatchStarted"){
        menuSound->stop();
        this->close();
    }
    else if(order == "MatchStartRefused"){
        QMessageBox::critical(nullptr, "Match Start ERROR", "Other Player Refused To Play");
    }
}

void Menu::on_pushButton_4_clicked()
{
    emit Back();
    menuSound->stop();
    this->close();
}


void Menu::on_pushButton_clicked()
{
    player->sendMessage("LetsPlay|"+player->username);
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

void Menu::gameStarted()
{
    menuSound->stop();
    this->close();
}

void Menu::matchFinished()
{
    menuSound->play();
    this->show();
}

