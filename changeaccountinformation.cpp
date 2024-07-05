#include "changeaccountinformation.h"
#include "ui_changeaccountinformation.h"

ChangeAccountInformation::ChangeAccountInformation(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChangeAccountInformation)
{
    ui->setupUi(this);
}

ChangeAccountInformation::~ChangeAccountInformation()
{
    delete ui;
}
