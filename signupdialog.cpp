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
        QMessageBox::critical(nullptr, "SignUp ERROR", "Invalid Email");
    }
    if(ui->phone->text().length() != 11){
        QMessageBox::critical(nullptr, "SignUp ERROR", "Invalid Phone Number");
    }
    if(ui->password->text().length() < 8){
        QMessageBox::critical(nullptr, "SignUp ERROR", "Password Should Have At least 8 Characters");
    }
    else if (ui->email->text().contains("@") && ui->email->text().contains(".com") && ui->phone->text().length() == 11 && ui->password->text().length() >=8){
    emit signupInformationEntered(ui->username->text(),ui->password->text(),ui->name->text(),ui->phone->text(),ui->email->text());
    this->close();
    }
}
void SignupDialog::on_buttonBox_rejected()
{
    this->close();
}

void SignupDialog::getOrderOfClient(QString order)
{
    if(order == "SingupErrorOfusername"){
        QMessageBox::critical(nullptr, "SignUp ERROR", "This Username Allready Exist");
    }else if(order == "SingupErrorOfPhoneNumeber"){
        QMessageBox::critical(nullptr, "SignUp ERROR", "This PhoneNumber Allready SignedUp");
    }else if (order == "SignedUP"){
        QMessageBox::critical(nullptr, "Signed UP", "You SignedUp SuccesFully");
        this->close();
    }
}

