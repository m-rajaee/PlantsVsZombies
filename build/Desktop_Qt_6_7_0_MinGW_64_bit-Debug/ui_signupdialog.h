/********************************************************************************
** Form generated from reading UI file 'signupdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPDIALOG_H
#define UI_SIGNUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_SignupDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *name;
    QLineEdit *username;
    QLineEdit *phone;
    QLineEdit *email;
    QLineEdit *password;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SignupDialog)
    {
        if (SignupDialog->objectName().isEmpty())
            SignupDialog->setObjectName("SignupDialog");
        SignupDialog->resize(400, 300);
        label = new QLabel(SignupDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 30, 49, 16));
        label_2 = new QLabel(SignupDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 60, 81, 16));
        label_3 = new QLabel(SignupDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 90, 101, 16));
        label_4 = new QLabel(SignupDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 120, 91, 16));
        label_5 = new QLabel(SignupDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(40, 150, 71, 16));
        name = new QLineEdit(SignupDialog);
        name->setObjectName("name");
        name->setGeometry(QRect(170, 30, 113, 22));
        username = new QLineEdit(SignupDialog);
        username->setObjectName("username");
        username->setGeometry(QRect(170, 60, 113, 22));
        phone = new QLineEdit(SignupDialog);
        phone->setObjectName("phone");
        phone->setGeometry(QRect(170, 90, 113, 22));
        email = new QLineEdit(SignupDialog);
        email->setObjectName("email");
        email->setGeometry(QRect(170, 120, 113, 22));
        password = new QLineEdit(SignupDialog);
        password->setObjectName("password");
        password->setGeometry(QRect(170, 150, 113, 22));
        buttonBox = new QDialogButtonBox(SignupDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(100, 230, 156, 24));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(SignupDialog);

        QMetaObject::connectSlotsByName(SignupDialog);
    } // setupUi

    void retranslateUi(QDialog *SignupDialog)
    {
        SignupDialog->setWindowTitle(QCoreApplication::translate("SignupDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SignupDialog", "Name : ", nullptr));
        label_2->setText(QCoreApplication::translate("SignupDialog", "User Name : ", nullptr));
        label_3->setText(QCoreApplication::translate("SignupDialog", "Phone Number : ", nullptr));
        label_4->setText(QCoreApplication::translate("SignupDialog", "Email Address : ", nullptr));
        label_5->setText(QCoreApplication::translate("SignupDialog", "Password :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignupDialog: public Ui_SignupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPDIALOG_H
