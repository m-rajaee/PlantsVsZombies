#include "resource.h"
#include <QGraphicsScene>
#include <QCursor>
Resource::Resource(ResourceType type) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    if(type == Sun){
        setPixmap(QPixmap(":/image/sun.png"));
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &Resource::Destroy);
        timer->start(4500);
        setScale(1.7);
    }else if(type == Brain){
        setPixmap(QPixmap(":/image/Brain.png"));
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &Resource::Destroy);
        timer->start(4500);
        setScale(0.2);
    }
}

void Resource::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit Collected();
        scene()->removeItem(this);
        delete this;
    }
}


void Resource::Destroy()
{
    scene()->removeItem(this);
    delete this;
}
