#include "zombies.h"
#include "ui_zombies.h"

Zombies::Zombies(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Zombies)
{
    ui->setupUi(this);
}

Zombies::~Zombies()
{
    delete ui;
}
