#ifndef PLANTCARD_H
#define PLANTCARD_H

#include <QGraphicsPixmapItem>
#include <QObject>

class PlantCard : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum PlantCardType {
        PeaShooter, TwoPeaShooter, Walnut, PlumMine, Jalapeno, Boomerang
    };
    PlantCard(PlantCardType type);
    PlantCardType type;
    int price;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void selected(PlantCard*);
};

#endif // PLANTCARD_H
