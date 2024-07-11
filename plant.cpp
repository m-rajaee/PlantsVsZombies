#include "Plant.h"
#include "zombie.h"
#include "bullet.h"
#include <QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
Plant::Plant(PlantType type, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), Type(type) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    if (type == PeaShooter) {
        health = 200;
        firingRate = 2;
        attackPower = 75;
        shootTimer = new QTimer();
        connect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));
        shootTimer->start(firingRate*1000);
        gifTimer = new QTimer();
        gif = new QMovie(":/gif/Peashooter.gif");
        gif->start();
        connect(gifTimer,SIGNAL(timeout()),this,SLOT(updatePixmapFromGif()));
        gifTimer->start(1);
    } else if (type == TwoPeaShooter) {
        health = 200;
        firingRate = 1;
        attackPower = 120;
        shootTimer = new QTimer();
        connect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));
        shootTimer->start(firingRate*1000);
        gifTimer = new QTimer();
        gif = new QMovie(":/gif/Repeater.gif");
        gif->start();
        connect(gifTimer,SIGNAL(timeout()),this,SLOT(updatePixmapFromGif()));
        gifTimer->start(1);
    }
    else if (type == Walnut) {
        health = 400;
        firingRate = 0;
        attackPower = 0;
        gifTimer = new QTimer();
        gif = new QMovie(":/gif/WallNut.gif");
        gif->start();
        connect(gifTimer,SIGNAL(timeout()),this,SLOT(updatePixmapFromGif()));
        gifTimer->start(1);
    }
    else if (type == PlumMine) {
        health = 2000;
        firingRate = 0;
        attackPower = 1500;
        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Plant::plumMineExplode);
        shootTimer->start(100);
        gifTimer = new QTimer();
        gif = new QMovie(":/gif/Boom.gif");
        gif->start();
        connect(gifTimer,SIGNAL(timeout()),this,SLOT(updatePixmapFromGif()));
        gifTimer->start(50);
    }
    else if (type == Jalapeno) {
        health = 2000;
        firingRate = 0;
        attackPower = 900;
        shootTimer = new QTimer();
        connect(shootTimer, SIGNAL(timeout()), this, SLOT(jalapenoExplode()));
        shootTimer->start(100);
        gifTimer = new QTimer();
        gif = new QMovie(":/gif/JalapenoAttack.gif");
        gif->start();
        connect(gifTimer,SIGNAL(timeout()),this,SLOT(updatePixmapFromGif()));
        gifTimer->start(50);
    }
    else if (type == Boomerang) {
        setPixmap(QPixmap(":/image/boomrang_transparent.png"));
        setScale(0.2);
        health = 200;
        firingRate = 2;
        attackPower = 90;
        shootTimer = new QTimer();
        connect(shootTimer, SIGNAL(timeout()), this, SLOT(jalapenoExplode()));
        shootTimer->start(firingRate*1000);
    }
    if(type == Jalapeno){
        QSoundEffect* Sound = new QSoundEffect();
        Sound->setSource(QUrl::fromLocalFile(":/audio/JalapenoExplode.wav"));
        Sound->setVolume(0.5);
        Sound->play();
    }else if (type == PlumMine){
        QSoundEffect* Sound = new QSoundEffect();
        Sound->setSource(QUrl::fromLocalFile(":/audio/PlumMine.wav"));
        Sound->setVolume(0.5);
        Sound->play();
    }
    else{
        if(type == Boomerang)
            setScale(0.2);
        else
            setScale(0.8);
    QSoundEffect* Sound = new QSoundEffect();
    Sound->setSource(QUrl::fromLocalFile(":/audio/Kasht.wav"));
    Sound->setVolume(0.5);
    Sound->play();
    }
}

void Plant::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        qDebug() << event->pos();
    }
}

void Plant::shoot() {
    Bullet* bullet = new Bullet(attackPower);
    if(Type == Boomerang)
        bullet->isBoomerangBullet = true;
    bullet->setPos(x()+60,y());
    scene()->addItem(bullet);
}

void Plant::jalapenoExplode()
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

void Plant::plumMineExplode()
{
    QRectF rect(x()-200,y()-135,400,400);
    qDebug() << rect;
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

void Plant::updatePixmapFromGif()
{
    setPixmap(gif->currentPixmap());
}
