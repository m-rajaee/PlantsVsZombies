#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <QMovie>
class Plant : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum PlantType {
        PeaShooter, TwoPeaShooter, Walnut, PlumMine, Jalapeno, Boomerang
    };
    Plant(PlantType type, QGraphicsItem *parent = nullptr);
    PlantType Type;
    QTimer *shootTimer;
    int health;
    int firingRate;
    int attackPower;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private slots:
    void shoot();
    void jalapenoExplode();
    void plumMineExplode();
    void updatePixmapFromGif();
private:
    QMovie* gif;
    QTimer* gifTimer;
};

#endif // PLANT_H
