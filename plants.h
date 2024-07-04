#ifndef PLANTS_H
#define PLANTS_H

#include <QDialog>

namespace Ui {
class Plants;
}

class Plants : public QDialog
{
    Q_OBJECT

public:
    explicit Plants(QWidget *parent = nullptr);
    ~Plants();

private:
    Ui::Plants *ui;
};

#endif // PLANTS_H
