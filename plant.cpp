#include "Plant.h"
#include "zombie.h"
#include "bullet.h"
#include <QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
Plant::Plant(PlantType type, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), type(type) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    if (type == PeaShooter) {
        setPixmap(QPixmap(":/image/peashooter transparent.png"));
        health = 200;
        firingRate = 2;
        attackPower = 150;
        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Plant::shoot);
        shootTimer->start(firingRate*1000);
    } else if (type == TwoPeaShooter) {
        setPixmap(QPixmap(":/image/two_peashooter_transparent.png"));
        health = 200;
        firingRate = 1;
        attackPower = 400;
        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Plant::shoot);
        shootTimer->start(firingRate*1000);
    }
    else if (type == Walnut) {
        setPixmap(QPixmap(":/image/walnut_transparent.png"));
        health = 400;
        firingRate = 0;
        attackPower = 0;
    }
    else if (type == PlumMine) {
        setPixmap(QPixmap(":/image/plum mine_transparent.png"));
        health = 2000;
        firingRate = 0;
        attackPower = 5000;
        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Plant::PlumMineExplode);
        shootTimer->start(2500);
    }
    else if (type == Jalapeno) {
        setPixmap(QPixmap(":/image/jalapino_transparent.png"));
        health = 2000;
        firingRate = 0;
        attackPower = 3000;
        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Plant::JalapenoExplode);
        shootTimer->start(2500);
    }
    else if (type == Boomerang) {
        setPixmap(QPixmap(":/image/boomrang_transparent.png"));
        health = 200;
        firingRate = 2;
        attackPower = 300;
        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Plant::shoot);
        shootTimer->start(firingRate*1000);
    }
    if(type == Boomerang)
        setScale(0.2);
    else
        setScale(0.065);
}

void Plant::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        qDebug() << event->pos();
    }
}

void Plant::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void Plant::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void Plant::shoot() {
    Bullet* bullet = new Bullet(attackPower);
    bullet->setPos(x(),y());
    scene()->addItem(bullet);
}

void Plant::JalapenoExplode()
{
    QRectF rect(0,y()-50,scene()->width(),100);
    QList<QGraphicsItem*> items = scene()->items(rect);
    for(QGraphicsItem* item : items){
        if(Zombie* zombie = dynamic_cast<Zombie*>(item)){
            zombie->health -= attackPower;
            if(zombie->health <= 0){
                scene()->removeItem(zombie);
                delete zombie;
            }
    }
    }
    scene()->removeItem(this);
    shootTimer->stop();
    delete this;
}

void Plant::PlumMineExplode()
{
    QRectF rect(x()-200,y()-200,400,400);
    QList<QGraphicsItem*> items = scene()->items(rect);
    for(QGraphicsItem* item : items){
        if(Zombie* zombie = dynamic_cast<Zombie*>(item)){
            zombie->health -= attackPower;
            if(zombie->health <= 0){
                scene()->removeItem(zombie);
                delete zombie;
            }
        }
    }
    scene()->removeItem(this);
    shootTimer->stop();
    delete this;
}
