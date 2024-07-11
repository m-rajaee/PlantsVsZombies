#include "letsplay.h"
#include "ui_letsplay.h"

LetsPlay::LetsPlay(Client* c,QString Oponnent,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LetsPlay)
{
    oponnent = Oponnent;
    ui->setupUi(this);
    player = c;
    ui->label->setText(Oponnent + "  Invited You To Start A Match");
}

LetsPlay::~LetsPlay()
{
    delete ui;
}

void LetsPlay::on_pushButton_2_clicked()
{
    player->sendMessage("MatchStartRefused");
    this->close();
}


void LetsPlay::on_pushButton_clicked()
{
    player->data.oponnent = oponnent;
    player->sendMessage("MatchStarted");
    emit matchStarted();
    this->close();
}

