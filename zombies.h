#ifndef ZOMBIES_H
#define ZOMBIES_H

#include <QDialog>

namespace Ui {
class Zombies;
}

class Zombies : public QDialog
{
    Q_OBJECT

public:
    explicit Zombies(QWidget *parent = nullptr);
    ~Zombies();

private:
    Ui::Zombies *ui;
};

#endif // ZOMBIES_H
