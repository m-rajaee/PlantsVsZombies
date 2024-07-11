#ifndef PLANTGAME_H
#define PLANTGAME_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "zombie.h"
#include "plant.h"
#include "plantcard.h"
#include <QGraphicsView>
#include "client.h"
#include "resource.h"
#include <QMouseEvent>
class PlantGame : public QGraphicsView
{
    Q_OBJECT
public:
    PlantGame(Client* c);
    void spawnZombie(Zombie::ZombieType type,int x, int y);
private slots:
    void GetOrderOfClient(QString order);
    void UpdateStatus();
    void AddSource();
    void CollectResource();
    void setSelectedCart(PlantCard* selectedcard);
    void clicked(QPointF clickedplace);
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Client* player;
    QGraphicsTextItem* RoundTimerItem;
    int seconds;
    int sun;
    PlantCard* SelectedCard;
    QVector<QPointF> planted;

};

#endif // PLANTGAME_H
