#ifndef START_H
#define START_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include "client.h"
#include "Authorization.h"
#include <QLineEdit>
namespace Ui {
class Start;
}

class Start : public QDialog
{
    Q_OBJECT

public:
    explicit Start(Client* c,QWidget *parent = nullptr);
    ~Start();
private slots:
    void gotologin();
private:
    Ui::Start *ui;
    QPushButton *start_button;
    QVBoxLayout *main_layout;
    Client* player;
    QLineEdit* ip;
    QLineEdit* port;
};

#endif // START_H

