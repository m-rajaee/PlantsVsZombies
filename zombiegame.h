#ifndef ZOMBIEGAME_H
#define ZOMBIEGAME_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include "zombie.h"
#include "plant.h"
#include <QGraphicsView>
#include "client.h"
#include "resource.h"
#include "zombiecard.h"
#include "mouse.h"
class ZombieGame : public QGraphicsView
{
    Q_OBJECT
public:
    ZombieGame(Client* c);
    void spawnPlant(Plant::PlantType type, int x , int y);

private slots:
    void GetOrderOfClient(QString order);
    void UpdateStatus();
    void AddSource();
    void CollectResource();
    void Won();
    void setSelectedCart(ZombieCard* selectedcard);
    void clicked(QPointF clickedplace);
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Client* player;
    QGraphicsTextItem* RoundTimerItem;
    int seconds;
    int brain;
    ZombieCard* SelectedCard;
};

#endif // ZOMBIEGAME_H
