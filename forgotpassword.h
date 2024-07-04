#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>

namespace Ui {
class ForgotPassword;
}

class ForgotPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = nullptr);
    ~ForgotPassword();
signals:
    void ChangeForgotedPassword(QString,QString);
private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::ForgotPassword *ui;
};

#endif // FORGOTPASSWORD_H