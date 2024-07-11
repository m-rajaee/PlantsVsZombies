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
#include "emoji.h"
class ZombieGame : public QGraphicsView
{
    Q_OBJECT
public:
    ZombieGame(Client* c);
    void spawnPlant(Plant::PlantType type, int x , int y);

private slots:
    void getOrderOfClient(QString order);
    void updateStatus();
    void addResource();
    void collectResource();
    void won();
    void setSelectedCart(ZombieCard* selectedcard);
    void clicked(QPointF clickedplace);
    void sendEmoji(Emoji* emoji);
    void setCardsOpacity();
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Client* player;
    QGraphicsTextItem* roundTimerItem;
    int secondsRemaining;
    int amountOfBrain;
    ZombieCard* selectedCard;
    ZombieCard* BucketHeadCard;
    ZombieCard* PurpleHairCard;
    ZombieCard* RegularCard;
    ZombieCard* TallCard;
    ZombieCard* LeafHeadCard;
    ZombieCard* AstronautCard;
};

#endif // ZOMBIEGAME_H
