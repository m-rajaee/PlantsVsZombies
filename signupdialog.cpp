#include "signupdialog.h"
#include "ui_signupdialog.h"

SignupDialog::SignupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignupDialog)
{
    ui->setupUi(this);
}

SignupDialog::~SignupDialog()
{
    delete ui;
}

void SignupDialog::on_buttonBox_accepted() {
    if(!ui->email->text().contains("@") || !ui->email->text().contains(".com")){
        QMessageBox::critical(nullptr, "ERROR", "Invalid Email");
    }
    if(ui->phone->text().length() != 11){
        QMessageBox::critical(nullptr, "ERROR", "Invalid Phone Number");
    }
    else if (ui->email->text().contains("@") && ui->email->text().contains(".com") && ui->phone->text().length() == 11){
    emit SignupInformation_Entered(ui->username->text(),ui->password->text(),ui->name->text(),ui->phone->text(),ui->email->text());
    this->close();
    }
}
void SignupDialog::on_buttonBox_rejected()
{
    this->close();
}
