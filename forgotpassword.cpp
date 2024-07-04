#include "forgotpassword.h"
#include "ui_forgotpassword.h"

ForgotPassword::ForgotPassword(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);
}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword::on_buttonBox_rejected()
{
    this->close();
}


void ForgotPassword::on_buttonBox_accepted()
{
    emit ChangeForgotedPassword(ui->lineEdit->text(),ui->lineEdit_2->text());
    this->close();
}

