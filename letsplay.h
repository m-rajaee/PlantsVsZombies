#ifndef LETSPLAY_H
#define LETSPLAY_H

#include <QDialog>
#include "client.h"
namespace Ui {
class LetsPlay;
}

class LetsPlay : public QDialog
{
    Q_OBJECT

public:
    explicit LetsPlay(Client* c,QString Oponnent,QWidget *parent = nullptr);
    ~LetsPlay();
signals:
    void matchStarted();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::LetsPlay *ui;
    Client* player;
    QString oponnent;
};

#endif // LETSPLAY_H
