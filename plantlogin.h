#ifndef PLANTLOGIN_H
#define PLANTLOGIN_H

#include <QMainWindow>

namespace Ui {
class PlantLogin;
}

class PlantLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlantLogin(QWidget *parent = nullptr);
    ~PlantLogin();

private:
    Ui::PlantLogin *ui;
};

#endif // PLANTLOGIN_H
