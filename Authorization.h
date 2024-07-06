#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H
#include "client.h"
#include <QMainWindow>
namespace Ui {
class Authorization;
}

class Authorization : public QMainWindow
{
    Q_OBJECT

public:
    explicit Authorization(Client* c,QWidget *parent = nullptr);
    ~Authorization();
private slots:
    void on_pushButton_2_clicked();
    void Get_Entered_Data(QString username,QString password,QString name,QString phone,QString address);
    void on_pushButton_clicked();
    void Resetpassword(QString phone,QString newpass);
    void on_pushButton_3_clicked();
    void GetOrderOfClient(QString order);
    void GetBack();
private:
    Ui::Authorization *ui;
    Client* player;
};

#endif // AUTHORIZATION_H
