#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include <QMessageBox>
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
    emit changeForgotedPassword(ui->lineEdit->text(),ui->lineEdit_2->text());
    this->close();
}

void ForgotPassword::getOrderOfClient(QString order)
{
    if(order == "PasswordResetError"){
        QMessageBox::critical(nullptr, "Password Reset ERROR", "No User With this Phone Number Exist");
    }else if (order == "PasswordReseted"){
        QMessageBox::critical(nullptr, "Password Reseted", "Password Reseted SuccesFully");
        this->close();
    }
}

