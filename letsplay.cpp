#include "letsplay.h"
#include "ui_letsplay.h"

LetsPlay::LetsPlay(Client* c,QString Oponnent,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LetsPlay)
{
    ui->setupUi(this);
    player = c;
    connect(player,SIGNAL(Order(QString)),this,SLOT(GetOrderOfClient(QString)));
    ui->label->setText(Oponnent + "  Invited You To Start A Match");
}

LetsPlay::~LetsPlay()
{
    delete ui;
}

void LetsPlay::on_pushButton_2_clicked()
{
    player->SendMessage("MatchStartRefused");
    this->close();
}


void LetsPlay::on_pushButton_clicked()
{
    player->SendMessage("MatchStarted");
    this->close();
}

void LetsPlay::GetOrderOfClient(QString order)
{

}

