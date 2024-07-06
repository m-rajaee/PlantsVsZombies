#ifndef CHANGEACCOUNTINFORMATION_H
#define CHANGEACCOUNTINFORMATION_H

#include <QDialog>
#include "client.h"
namespace Ui {
class ChangeAccountInformation;
}

class ChangeAccountInformation : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeAccountInformation(Client* c,QWidget *parent = nullptr);
    ~ChangeAccountInformation();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void GetOrderOfClient(QString order);

private:
    Ui::ChangeAccountInformation *ui;
    Client * player;
};

#endif // CHANGEACCOUNTINFORMATION_H
