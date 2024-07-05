#ifndef CHANGEACCOUNTINFORMATION_H
#define CHANGEACCOUNTINFORMATION_H

#include <QDialog>

namespace Ui {
class ChangeAccountInformation;
}

class ChangeAccountInformation : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeAccountInformation(QWidget *parent = nullptr);
    ~ChangeAccountInformation();

private:
    Ui::ChangeAccountInformation *ui;
};

#endif // CHANGEACCOUNTINFORMATION_H
