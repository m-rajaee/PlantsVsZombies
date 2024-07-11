#include "plantcard.h"
#include <QGraphicsSceneMouseEvent>
PlantCard::PlantCard(PlantCardType type) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    this->type = type;
    if (type == PeaShooter) {
        setPixmap(QPixmap(":/image/pea shooter.jpg"));
        price = 50;
    } else if (type == TwoPeaShooter) {
        setPixmap(QPixmap(":/image/two_peashooter.jpg"));
        price = 100;
    }
    else if (type == Walnut) {
        setPixmap(QPixmap(":/image/walnut.jpg"));
        price = 100;
    }
    else if (type == PlumMine) {
        setPixmap(QPixmap(":/image/plum mine.jpg"));
        price = 175;
    }
    else if (type == Jalapeno) {
        setPixmap(QPixmap(":/image/jalapino.jpg"));
        price = 150;
    }
    else if (type == Boomerang) {
        setPixmap(QPixmap(":/image/boomerang.jpg"));
        price = 125;
    }
    setOpacity(0.14);
    if(type == Boomerang)
        setScale(0.2);
    else
    setScale(0.065);
}

void PlantCard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit selected(this);
}
