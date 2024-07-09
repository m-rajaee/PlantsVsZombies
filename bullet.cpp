#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include "zombie.h"
Bullet::Bullet(int attackPower) {
    isBoomreng = false;
    AttackPower = attackPower;
    setRect(0,0,30,30);
    setBrush(QBrush(Qt::green));
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),SLOT(move()));
    timer->start(50); //every 50 miliseconds timeouts
}

void Bullet::move()
{
    // check if bullet colide with an enemy
    QList<QGraphicsItem*> collidingItems = scene()->collidingItems(this);
    for(QGraphicsItem* item : collidingItems){
        if(Zombie* zombie = dynamic_cast<Zombie*>(item)){
            zombie->health -= AttackPower;
            if(zombie->health <= 0){
                scene()->removeItem(zombie);
                delete zombie;
            }
            if(!isBoomreng){
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
