#include "plantsmenu.h"
#include "ui_plantsmenu.h"
#include "changeaccountinformation.h"
#include <QMessageBox>
PlantsMenu::PlantsMenu(Client* c,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlantsMenu)
{
    ui->setupUi(this);
    plants = c;
    connect(plants,SIGNAL(Order(QString)),this,SLOT(GetOrderOfClient(QString)));
}

PlantsMenu::~PlantsMenu()
{
    delete ui;
}

void PlantsMenu::GetOrderOfClient(QString order)
{
    if (order == "ChangeInformationError"){

    }else if (order == "InformationChanged"){
        QMessageBox::critical(nullptr, "Login ERROR", "Username Or Password is Wrong");
    }else if (order == ""){

    }
}

void PlantsMenu::on_pushButton_4_clicked()
{
    emit Back();
}


void PlantsMenu::on_pushButton_clicked()
{

}


void PlantsMenu::on_pushButton_2_clicked()
{

}


void PlantsMenu::on_pushButton_3_clicked()
{

}

