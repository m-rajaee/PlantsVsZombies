#ifndef BULLET_H
#define BULLET_H
#include <QObject>
#include <QGraphicsEllipseItem>
#include <QSoundEffect>
class Bullet :public QObject ,public QGraphicsEllipseItem{
    Q_OBJECT
public:
    Bullet(int attackPower);
private slots:
    void move();
private:
    int AttackPower;
};

#endif // BULLET_H
