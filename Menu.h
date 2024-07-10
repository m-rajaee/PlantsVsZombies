#ifndef MENU_H
#define MENU_H
#include "client.h"
#include <QDialog>
#include <QSoundEffect>
namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(Client* c,QWidget *parent = nullptr);
    ~Menu();
private slots:
    void GetOrderOfClient(QString order);
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void gameStarted();
    void MatchFinished();

signals:
    void Back();
private:
    Ui::Menu *ui;
    Client* player;
    QSoundEffect* MenuSound;
};

#endif // MENU_H
