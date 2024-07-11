#include "zombiecard.h"
#include <QGraphicsSceneMouseEvent>
ZombieCard::ZombieCard(ZombieCardType type) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    this->type = type;
    if (type == Regular) {
        setPixmap(QPixmap(":/image/regular zombie.jpg"));
        price = 100;
    } else if (type == BucketHead) {
        setPixmap(QPixmap(":/image/Bucket head zombie.jpg"));
        price = 200;
    }
    else if (type == LeafHead) {
        setPixmap(QPixmap(":/image/leaf hair zombie.jpg"));
        price = 150;
    }
    else if (type == Tall) {
        setPixmap(QPixmap(":/image/tall zombie.jpg"));
        price = 150;
    }
    else if (type == Astronaut) {
        setPixmap(QPixmap(":/image/astronaut zombie.jpg"));
        price = 200;
    }
    else if (type == PurpleHair) {
        setPixmap(QPixmap(":/image/purple hair zombie.jpg"));
        price = 800;
    }
    setOpacity(0.14);
    setScale(0.065);
}

void ZombieCard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit selected(this);
}
