#ifndef ZOMBIESLOGIN_H
#define ZOMBIESLOGIN_H

#include <QMainWindow>
#include "client.h"
namespace Ui {
class ZombiesLogin;
}

class ZombiesLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit ZombiesLogin(Client* c,QWidget *parent = nullptr);
    ~ZombiesLogin();

private slots:
    void on_pushButton_2_clicked();
    void Get_Entered_Data(QString username,QString password,QString name,QString phone,QString address);
    void on_pushButton_clicked();
    void Resetpassword(QString phone,QString newpass);
    void on_pushButton_3_clicked();
    void GetOrderOfClient(QString order);
    void GetBack();
private:
    Ui::ZombiesLogin *ui;
    Client* zombies;
};

#endif // ZOMBIESLOGIN_H
