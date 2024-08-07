#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include "zombie.h"
Bullet::Bullet(int attackPower) {
    isBoomerangBullet = false;
    AttackPower = attackPower;
    setRect(0,0,25,25);
    setBrush(QBrush(Qt::green));
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),SLOT(move()));
    timer->start(50);
}

void Bullet::move()
{

    QList<QGraphicsItem*> collidingItems = scene()->collidingItems(this);
    for(QGraphicsItem* item : collidingItems){
        if(Zombie* zombie = dynamic_cast<Zombie*>(item)){
            zombie->health -= AttackPower;
            if(zombie->health <= 0){
                scene()->removeItem(zombie);
                delete zombie;
            }
            if(!isBoomerangBullet){
            scene()->removeItem(this);
            delete this;
            return;
            }
        }
    }
    // moving bullet to the right
    setPos(x()+10,y());
    if(pos().x() > scene()->sceneRect().width() ){
        scene()->removeItem(this);
        delete this;
    }
}
