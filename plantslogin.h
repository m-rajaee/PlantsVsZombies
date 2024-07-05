#ifndef PLANTSLOGIN_H
#define PLANTSLOGIN_H
#include "client.h"
#include <QMainWindow>
namespace Ui {
class PlantsLogin;
}

class PlantsLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlantsLogin(Client* c,QWidget *parent = nullptr);
    ~PlantsLogin();
private slots:
    void on_pushButton_2_clicked();
    void Get_Entered_Data(QString username,QString password,QString name,QString phone,QString address);
    void on_pushButton_clicked();
    void Resetpassword(QString phone,QString newpass);
    void on_pushButton_3_clicked();
    void GetOrderOfClient(QString order);
    void GetBack();
private:
    Ui::PlantsLogin *ui;
    Client* plants;
};

#endif // PLANTSLOGIN_H
