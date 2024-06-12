#include "SuccesfullLogin.h"
#include "ui_SuccesfullLogin.h"

SuccesfullLogin::SuccesfullLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

SuccesfullLogin::~SuccesfullLogin()
{
    delete ui;
}

void SuccesfullLogin::on_pushButton_clicked()
{
    this->close();
}

