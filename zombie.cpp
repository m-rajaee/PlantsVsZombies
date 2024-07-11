#include "Zombie.h"
#include "plant.h"
#include <QGraphicsScene>
#include <QSoundEffect>
Zombie::Zombie(ZombieType type, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), type(type) {
    srand(time(NULL)); int a = rand()%4;
    QSoundEffect* Sound = new QSoundEffect();
    if(a == 0)
        Sound->setSource(QUrl::fromLocalFile(":/audio/groan3.wav"));
    else if(a == 1)
        Sound->setSource(QUrl::fromLocalFile(":/audio/groan4.wav"));
    else if(a == 2)
        Sound->setSource(QUrl::fromLocalFile(":/audio/groan5.wav"));
    else if(a == 3)
        Sound->setSource(QUrl::fromLocalFile(":/audio/groan6.wav"));
    Sound->setVolume(0.5);
    Sound->play();
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    isEating = false;
    if (type == Regular) {
        health = 500;
        movementDelay = 1;
        attackPower = 80;
        timeBetweenAttack = 1;
        gifTimer = new QTimer();
        gif = new QMovie(":/gif/Regular.gif");
        gif->start();
        connect(gifTimer,SIGNAL(timeout()),this,SLOT(Gif()));
        gifTimer->start(1);
    } else if (type == BucketHead) {
        health = 1950;
        movementDelay = 2;
        attackPower = 100;
        timeBetweenAttack = 1;
        gifTimer = new QTimer();
        gif = new QMovie(":/gif/Buckethead.gif");
        gif->start();
        connect(gifTimer,SIGNAL(timeout()),this,SLOT(Gif()));
        gifTimer->start(1);
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
    if(type == BucketHead)
        setScale(0.65);
    else if(type == Regular)
        setScale(0.65);
    else
        setScale(0.075);
    moveTimer = new QTimer();
    attackTimer = new QTimer();
    connect(attackTimer, SIGNAL(timeout()), this,SLOT(eat()));
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(movementDelay*50);
    attackTimer->start(timeBetweenAttack*1000);
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
    setPos(x()-1.9,y());
    if(x() <= 120){
        emit zombieWon();
        return;
    }
}

void Zombie::eat()
{
    if(!isEating) return;
    QSoundEffect* Sound = new QSoundEffect();
    Sound->setSource(QUrl::fromLocalFile(":/audio/Khordan.wav"));
    Sound->setVolume(0.5);
    Sound->play();
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

void Zombie::Gif()
{
    setPixmap(gif->currentPixmap());
}
