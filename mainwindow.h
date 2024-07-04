#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class PlantsLogin;
}
QT_END_NAMESPACE

class PlantsLogin : public QMainWindow
{
    Q_OBJECT

public:
    PlantsLogin(QWidget *parent = nullptr);
    ~PlantsLogin();

private slots:
    void on_pushButton_2_clicked();
    void Get_Entered_Information(QString Name,QString Username,QString PhoneNumber,QString Email,QString Password);
    void on_pushButton_clicked();

private:
    Ui::PlantsLogin *ui;
};
#endif // MAINWINDOW_H
