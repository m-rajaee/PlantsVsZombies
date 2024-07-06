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
    connect(player,SIGNAL(Order(QString)),this,SLOT(GetOrderOfClient(QString)));
    player->ShowHistory(player->Username);
}

void ShowHistory::GetOrderOfClient(QString order)
{
    QStringList parts = order.split("|");
    if(parts[0] == "ShowHistory"){
    QString history = parts[1];
    if (history.isEmpty()) {
        history = "No game history found for " + player->Username;
    }
    ui->textEdit->setPlainText(history);
    }
}

ShowHistory::~ShowHistory()
{
    delete ui;
}
