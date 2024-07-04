#include "plants.h"
#include "ui_plants.h"

Plants::Plants(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Plants)
{
    ui->setupUi(this);
}

Plants::~Plants()
{
    delete ui;
}
