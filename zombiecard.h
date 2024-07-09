#ifndef ZOMBIECARD_H
#define ZOMBIECARD_H

#include <QGraphicsPixmapItem>
#include <QObject>

class ZombieCard : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum ZombieCardType {
        Regular, BucketHead, LeafHead, Tall, Astronaut, PurpleHair
    };
    ZombieCard(ZombieCardType type);
    ZombieCardType type;
    int price;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void Selected(ZombieCard*);
};

#endif // ZOMBIECARD_H
