#include "showhistory.h"
#include "ui_showhistory.h"

ShowHistory::ShowHistory(Client* c,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowHistory)
{
    ui->setupUi(this);
    player = c;
}

ShowHistory::~ShowHistory()
{
    delete ui;
}
