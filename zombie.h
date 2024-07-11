#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class Zombie : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum ZombieType {
        Regular, BucketHead, LeafHead, Tall, Astronaut, PurpleHair
    };
    Zombie(ZombieType type, QGraphicsItem *parent = nullptr);
    ZombieType type;
    QTimer *moveTimer;
    QTimer* attackTimer;
    int health;
    int movementDelay;
    int attackPower;
    int timeBetweenAttack;
    bool isEating;
signals:
    void zombieWon();
private slots:
    void move();
    void eat();
    void Gif();
private:
    QMovie* gif;
    QTimer* gifTimer;

};

#endif // ZOMBIE_H
