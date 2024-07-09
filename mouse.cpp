#include "mouse.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
Mouse::Mouse() {
    setRect(0, 0,970,580); // Set rectangle size
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    setOpacity(0.001);
}

void Mouse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked(event->pos());
        qDebug() << event->pos();
    }
    QGraphicsRectItem::mousePressEvent(event);
}
