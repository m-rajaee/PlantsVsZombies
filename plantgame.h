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
#include "emoji.h"
#include "plantcard.h"
class PlantGame : public QGraphicsView
{
    Q_OBJECT
public:
    PlantGame(Client* c);
    void spawnZombie(Zombie::ZombieType type,int x, int y);
    void setCardsOpacity();
private slots:
    void getOrderOfClient(QString order);
    void updateStatus();
    void addSourceToScene();
    void collectResource();
    void setSelectedCart(PlantCard* selectedcard);
    void clicked(QPointF clickedplace);
    void sendEmoji(Emoji* emoji);
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Client* player;
    QGraphicsTextItem* roundTimerItem;
    int secondsRemaining;
    int amoutOfSun;
    PlantCard* selectedCard;
    QVector<QPointF> planted;
    PlantCard* BoomerangCard;
    PlantCard* JalapenoCard;
    PlantCard* PeaShooterCard;
    PlantCard* PlumMineCard;
    PlantCard* TwoPeaShooterCard;
    PlantCard* WalnutCard;

};

#endif // PLANTGAME_H
