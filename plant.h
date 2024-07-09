#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class Plant : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum PlantType {
        PeaShooter, TwoPeaShooter, Walnut, PlumMine, Jalapeno, Boomerang
    };
    Plant(PlantType type, QGraphicsItem *parent = nullptr);
    PlantType type;
    QTimer *shootTimer;
    int health;
    int firingRate;
    int attackPower;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private slots:
    void shoot();
    void JalapenoExplode();
    void PlumMineExplode();
signals:


};

#endif // PLANT_H
