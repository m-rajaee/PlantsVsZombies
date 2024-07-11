#ifndef SHOWHISTORY_H
#define SHOWHISTORY_H

#include <QDialog>
#include "client.h"
namespace Ui {
class ShowHistory;
}

class ShowHistory : public QDialog
{
    Q_OBJECT

public:
    explicit ShowHistory(Client* c,QWidget *parent = nullptr);
    ~ShowHistory();
private slots:
    void getOrderOfClient(QString order);
private:
    Ui::ShowHistory *ui;
    Client* player;
};

#endif // SHOWHISTORY_H
