#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QMessageBox>
namespace Ui {
class SignupDialog;
}

class SignupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignupDialog(QWidget *parent = nullptr);
    ~SignupDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
signals:
    void SignupInformation_Entered(QString,QString,QString,QString,QString);

private:
    Ui::SignupDialog *ui;
};

#endif // SIGNUPDIALOG_H
