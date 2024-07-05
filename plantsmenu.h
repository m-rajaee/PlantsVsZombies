#ifndef PLANTSMENU_H
#define PLANTSMENU_H
#include "client.h"
#include <QDialog>

namespace Ui {
class PlantsMenu;
}

class PlantsMenu : public QDialog
{
    Q_OBJECT

public:
    explicit PlantsMenu(Client* c,QWidget *parent = nullptr);
    ~PlantsMenu();
private slots:
    void GetOrderOfClient(QString order);
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void Back();
private:
    Ui::PlantsMenu *ui;
    Client* plants;
};

#endif // PLANTSMENU_H
