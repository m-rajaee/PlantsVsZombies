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
    void getEnteredData(QString username,QString password,QString name,QString phone,QString address);
    void on_pushButton_clicked();
    void resetPassword(QString phone,QString newpass);
    void on_pushButton_3_clicked();
    void getOrderOfClient(QString order);
    void getBackToTheAuthorizationPage();
private:
    Ui::Authorization *ui;
    Client* player;
};

#endif // AUTHORIZATION_H
