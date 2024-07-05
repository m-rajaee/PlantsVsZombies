#ifndef ZOMBIESMENU_H
#define ZOMBIESMENU_H
#include "client.h"
#include <QDialog>

namespace Ui {
class ZombiesMenu;
}

class ZombiesMenu : public QDialog
{
    Q_OBJECT

public:
    explicit ZombiesMenu(Client* c,QWidget *parent = nullptr);
    ~ZombiesMenu();
private slots:
    void GetOrderOfClient(QString order);
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();
signals:
    void Back();
private:
    Ui::ZombiesMenu *ui;
    Client* zombies;
};

#endif // ZOMBIESMENU_H
