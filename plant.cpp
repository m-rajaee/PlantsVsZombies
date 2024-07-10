#include "Plant.h"
#include "zombie.h"
#include "bullet.h"
#include <QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
Plant::Plant(PlantType type, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), type(type) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    if (type == PeaShooter) {
        health = 200;
        firingRate = 2;
        attackPower = 75;
        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Plant::shoot);
        shootTimer->start(firingRate*1000);
        giftimer = new QTimer();
        movie = new QMovie(":/gif/Peashooter.gif");
        movie->start();
        connect(giftimer,SIGNAL(timeout()),this,SLOT(gif()));
        giftimer->start(1);
    } else if (type == TwoPeaShooter) {
        health = 200;
        firingRate = 1;
        attackPower = 120;
        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Plant::shoot);
        shootTimer->start(firingRate*1000);
        giftimer = new QTimer();
        movie = new QMovie(":/gif/Repeater.gif");
        movie->start();
        connect(giftimer,SIGNAL(timeout()),this,SLOT(gif()));
        giftimer->start(1);
    }
    else if (type == Walnut) {
        health = 400;
        firingRate = 0;
        attackPower = 0;
        giftimer = new QTimer();
        movie = new QMovie(":/gif/WallNut.gif");
        movie->start();
        connect(giftimer,SIGNAL(timeout()),this,SLOT(gif()));
        giftimer->start(1);
    }
    else if (type == PlumMine) {
        health = 2000;
        firingRate = 0;
        attackPower = 5000;
        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Plant::PlumMineExplode);
        shootTimer->start(3500);
        giftimer = new QTimer();
        movie = new QMovie(":/gif/Boom.gif");
        movie->start();
        connect(giftimer,SIGNAL(timeout()),this,SLOT(gif()));
        giftimer->start(50);
    }
    else if (type == Jalapeno) {
        health = 2000;
        firingRate = 0;
        attackPower = 900;
        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Plant::JalapenoExplode);
        shootTimer->start(3500);
        giftimer = new QTimer();
        movie = new QMovie(":/gif/JalapenoAttack.gif");
        movie->start();
        connect(giftimer,SIGNAL(timeout()),this,SLOT(gif()));
        giftimer->start(50);
    }
    else if (type == Boomerang) {
        setPixmap(QPixmap(":/image/boomrang_transparent.png"));
        setScale(0.2);
        health = 200;
        firingRate = 2;
        attackPower = 90;
        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Plant::shoot);
        shootTimer->start(firingRate*1000);
    }
    if(type == Jalapeno){
        QSoundEffect* Sound = new QSoundEffect();
        Sound->setSource(QUrl::fromLocalFile(":/audio/JalapenoExplode.wav"));
        Sound->setVolume(0.4);
        Sound->play();
    }else if (type == PlumMine){
        QSoundEffect* Sound = new QSoundEffect();
        Sound->setSource(QUrl::fromLocalFile(":/audio/PlumMine.wav"));
        Sound->setVolume(0.4);
        Sound->play();
    }
    else{
        if(type == Boomerang)
            setScale(0.2);
        else
            setScale(0.8);
    QSoundEffect* Sound = new QSoundEffect();
    Sound->setSource(QUrl::fromLocalFile(":/audio/Kasht.wav"));
    Sound->setVolume(0.4);
    Sound->play();
    }
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
    if(type == Boomerang)
        bullet->isBoomerang = true;
    bullet->setPos(x()+60,y());
    scene()->addItem(bullet);
}

void Plant::JalapenoExplode()
{
    QRectF rect(0,y()-50,scene()->sceneRect().width(),100);
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
    delete this;
}

void Plant::gif()
{
    setPixmap(movie->currentPixmap());
}
