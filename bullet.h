#ifndef BULLET_H
#define BULLET_H
#include <QObject>
#include <QGraphicsPixmapItem>
class Bullet :public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(int attackPower);
    bool isBoomreng;
private slots:
    void move();
private:
    int AttackPower;
};

#endif // BULLET_H
