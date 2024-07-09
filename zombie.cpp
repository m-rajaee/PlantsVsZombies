#include "Zombie.h"
#include "plant.h"
#include <QGraphicsScene>
Zombie::Zombie(ZombieType type, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), type(type) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    isEating = false;
    if (type == Regular) {
        health = 500;
        movementDelay = 1;
        attackPower = 80;
        timeBetweenAttack = 1;
        setPixmap(QPixmap(":/image/regular zombie_transparent.png"));
    } else if (type == BucketHead) {
        health = 1950;
        movementDelay = 2;
        attackPower = 100;
        timeBetweenAttack = 1;
        setPixmap(QPixmap(":/image/Bucket head zombie_trasparent.png"));
    }
    else if (type == LeafHead) {
        health = 800;
        movementDelay = 1;
        attackPower = 80;
        timeBetweenAttack = 1;
        setPixmap(QPixmap(":/image/leaf hair zombie_transparent.png"));
    }
    else if (type == Tall) {
        health = 500;
        movementDelay = 1;
        attackPower = 90;
        timeBetweenAttack = 1;
        setPixmap(QPixmap(":/image/tall zombie_transparent.png"));
    }
    else if (type == Astronaut) {
        health = 500;
        movementDelay = 1; //first 1 others 0.5
        attackPower = 50;
        timeBetweenAttack = 1;//first 1 others 0.5
        setPixmap(QPixmap(":/image/astronaut zombie_transparent.png"));
    }
    else if (type == PurpleHair) {
        health = 4000;
        movementDelay = 1;
        attackPower = 75;
        timeBetweenAttack = 0.5;
        setPixmap(QPixmap(":/image/purple hair zombie_transparent.png"));
    }
    setScale(0.065);
    moveTimer = new QTimer();
    AttackTimer = new QTimer();
    connect(AttackTimer, &QTimer::timeout, this, &Zombie::eat);
    connect(moveTimer, &QTimer::timeout, this, &Zombie::move);
    moveTimer->start(movementDelay*1000);
    AttackTimer->start(timeBetweenAttack*1000);
}

void Zombie::move() {
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems) {
        if (Plant *plant = dynamic_cast<Plant *>(item)) {
            isEating = true;
            return;
    }
    }
    isEating = false;
    setPos(x()-18,y());
    if(x() <= 120){
        emit zombieWon();
        return;
    }
}

void Zombie::eat()
{
    if(!isEating) return;
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems) {
        if (Plant *plant = dynamic_cast<Plant *>(item)) {
            plant->health -= attackPower;
            if (plant->health <= 0) {
                scene()->removeItem(plant);
                delete plant;
                isEating = false;
            }
            return;
        }
    }
}
