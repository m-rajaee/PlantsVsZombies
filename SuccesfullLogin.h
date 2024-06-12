#ifndef SUCCESFULLLOGIN_H
#define SUCCESFULLLOGIN_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class SuccesfullLogin : public QDialog
{
    Q_OBJECT

public:
    explicit SuccesfullLogin(QWidget *parent = nullptr);
    ~SuccesfullLogin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // SUCCESFULLLOGIN_H
