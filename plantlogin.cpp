#include "plantlogin.h"
#include "ui_plantlogin.h"

PlantLogin::PlantLogin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlantLogin)
{
    ui->setupUi(this);
}

PlantLogin::~PlantLogin()
{
    delete ui;
}
