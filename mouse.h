#ifndef MOUSE_H
#define MOUSE_H

#include <QGraphicsRectItem>
#include <QObject>
class Mouse : public QObject , public QGraphicsRectItem
{
    Q_OBJECT
public:
    Mouse();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void clicked(QPointF);
};

#endif // MOUSE_H
