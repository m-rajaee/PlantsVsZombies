#include "showhistory.h"
#include "ui_showhistory.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
ShowHistory::ShowHistory(Client* c,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowHistory)
{
    ui->setupUi(this);
    player = c;
    connect(player,SIGNAL(Order(QString)),this,SLOT(getOrderOfClient(QString)));
    player->showHistory(player->username);
}

void ShowHistory::getOrderOfClient(QString order)
{
    QStringList orderParts = order.split("|");
    if(orderParts[0] == "ShowHistory"){
    QString history = orderParts[1];
    if (history.isEmpty()) {
        history = "No game history found for " + player->username;
    }
    ui->textEdit->setPlainText(history);
    }
}

ShowHistory::~ShowHistory()
{
    delete ui;
}
