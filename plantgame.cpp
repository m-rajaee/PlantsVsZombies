#include "plantgame.h"
#include "mouse.h"
#include "emoji.h"
#include<QGraphicsItem>
#include <QSoundEffect>
PlantGame::PlantGame(Client* c) {
    QSoundEffect* Sound = new QSoundEffect();
    Sound->setSource(QUrl::fromLocalFile(":/audio/Playing.wav"));
    Sound->setVolume(0.02);
    Sound->play();
    secondsRemaining = 210;
    amoutOfSun = 0;
    player = c;
    selectedCard=nullptr;
    QTimer* resourceTimer = new QTimer();
    connect(resourceTimer,SIGNAL(timeout()),this,SLOT(addSourceToScene()));
    resourceTimer->start(5000);
    connect(player,SIGNAL(Order(QString)),this,SLOT(getOrderOfClient(QString)));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(970,580);
    scene->setSceneRect(0,0,970,580);
    view->setBackgroundBrush(QBrush(QImage(":/image/filed.png")));
    //Adding Mouse Control
    Mouse* mouse = new Mouse(); mouse->setPos(120,100);
    scene->addItem(mouse);
    connect(mouse,SIGNAL(clicked(QPointF)),this,SLOT(clicked(QPointF)));
    //Adding Timer to Scene
    QTimer* RoundTimer = new QTimer();
    roundTimerItem = new QGraphicsTextItem();
    roundTimerItem->setDefaultTextColor(Qt::yellow);
    roundTimerItem->setFont(QFont("Arial",16));
    connect(RoundTimer,SIGNAL(timeout()),this,SLOT(updateStatus()));
    RoundTimer->start(1000); // Update every second
    scene->addItem(roundTimerItem);
    roundTimerItem->setPos(scene->sceneRect().width() - 230,10);
    //Adding Cards To scene
    BoomerangCard = new PlantCard(PlantCard::PlantCardType::Boomerang);
    BoomerangCard->setPos(10,10); scene->addItem(BoomerangCard);
    JalapenoCard = new PlantCard(PlantCard::PlantCardType::Jalapeno);
    JalapenoCard->setPos(110,10); scene->addItem(JalapenoCard);
    PeaShooterCard = new PlantCard(PlantCard::PlantCardType::PeaShooter);
    PeaShooterCard->setPos(210,10); scene->addItem(PeaShooterCard);
    PlumMineCard = new PlantCard(PlantCard::PlantCardType::PlumMine);
    PlumMineCard->setPos(310,10); scene->addItem(PlumMineCard);
    TwoPeaShooterCard = new PlantCard(PlantCard::PlantCardType::TwoPeaShooter);
    TwoPeaShooterCard->setPos(410,10); scene->addItem(TwoPeaShooterCard);
    WalnutCard = new PlantCard(PlantCard::PlantCardType::Walnut);
    WalnutCard->setPos(510,10); scene->addItem(WalnutCard);
    connect(BoomerangCard,SIGNAL(selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
    connect(JalapenoCard,SIGNAL(selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
    connect(PeaShooterCard,SIGNAL(selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
    connect(PlumMineCard,SIGNAL(selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
    connect(TwoPeaShooterCard,SIGNAL(selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
    connect(WalnutCard,SIGNAL(selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
    // Show Prices
    QGraphicsTextItem* BoomerangCardPrice = new QGraphicsTextItem();
    QGraphicsTextItem* JalapenoCardPrice = new QGraphicsTextItem();
    QGraphicsTextItem* PeaShooterCardPrice = new QGraphicsTextItem();
    QGraphicsTextItem* PlumMineCardPrice = new QGraphicsTextItem();
    QGraphicsTextItem* TwoPeaShooterCardPrice = new QGraphicsTextItem();
    QGraphicsTextItem* WalnutCardPrice = new QGraphicsTextItem();
    BoomerangCardPrice->setDefaultTextColor(Qt::yellow);
    BoomerangCardPrice->setFont(QFont("Arial",12));BoomerangCardPrice->setPlainText("125"); BoomerangCardPrice->setPos(25,80); scene->addItem(BoomerangCardPrice);
    JalapenoCardPrice->setDefaultTextColor(Qt::yellow);
    JalapenoCardPrice->setFont(QFont("Arial",12));JalapenoCardPrice->setPlainText("150"); JalapenoCardPrice->setPos(125,80); scene->addItem(JalapenoCardPrice);
    PeaShooterCardPrice->setDefaultTextColor(Qt::yellow);
    PeaShooterCardPrice->setFont(QFont("Arial",12));PeaShooterCardPrice->setPlainText("50"); PeaShooterCardPrice->setPos(225,80); scene->addItem(PeaShooterCardPrice);
    PlumMineCardPrice->setDefaultTextColor(Qt::yellow);
    PlumMineCardPrice->setFont(QFont("Arial",12));PlumMineCardPrice->setPlainText("175"); PlumMineCardPrice->setPos(325,80); scene->addItem(PlumMineCardPrice);
    TwoPeaShooterCardPrice->setDefaultTextColor(Qt::yellow);
    TwoPeaShooterCardPrice->setFont(QFont("Arial",12));TwoPeaShooterCardPrice->setPlainText("100"); TwoPeaShooterCardPrice->setPos(425,80); scene->addItem(TwoPeaShooterCardPrice);
    WalnutCardPrice->setDefaultTextColor(Qt::yellow);
    WalnutCardPrice->setFont(QFont("Arial",12));WalnutCardPrice->setPlainText("100"); WalnutCardPrice->setPos(525,80); scene->addItem(WalnutCardPrice);
    //Show Username
    QGraphicsTextItem* username = new QGraphicsTextItem();
    username->setFont(QFont("Arial",16));username->setPlainText(player->username); username->setPos(590,3); scene->addItem(username);
    username->setDefaultTextColor(Qt::darkCyan);
    //Adding Emoji Cards
    Emoji* poker = new Emoji(Emoji::EmojiType::Poker);
    poker->setPos(590,34); scene->addItem(poker);
    connect(poker,SIGNAL(emojiSelected(Emoji*)),this,SLOT(sendEmoji(Emoji*)));
    Emoji* laugh = new Emoji(Emoji::EmojiType::Laugh);
    laugh->setPos(610,28); scene->addItem(laugh);
    connect(laugh,SIGNAL(emojiSelected(Emoji*)),this,SLOT(sendEmoji(Emoji*)));
    Emoji* rage = new Emoji(Emoji::EmojiType::Rage);
    rage->setPos(650,32); scene->addItem(rage);
    connect(rage,SIGNAL(emojiSelected(Emoji*)),this,SLOT(sendEmoji(Emoji*)));
    Emoji* sunglass = new Emoji(Emoji::EmojiType::SunGlass);
    sunglass->setPos(680,30); scene->addItem(sunglass);
    connect(sunglass,SIGNAL(emojiSelected(Emoji*)),this,SLOT(sendEmoji(Emoji*)));
    view->show();
}

void PlantGame::spawnZombie(Zombie::ZombieType type, int x, int y)
{
    QSoundEffect* Sound = new QSoundEffect(); srand(time(NULL)); int a = rand()%4;
    if(a == 0)
        Sound->setSource(QUrl::fromLocalFile(":/audio/groan3.wav"));
    else if(a == 1)
        Sound->setSource(QUrl::fromLocalFile(":/audio/groan4.wav"));
    else if(a == 2)
        Sound->setSource(QUrl::fromLocalFile(":/audio/groan5.wav"));
    else if(a == 3)
        Sound->setSource(QUrl::fromLocalFile(":/audio/groan6.wav"));
    Sound->setVolume(0.5);
    Sound->play();
    Zombie* zombie = new Zombie(type);
    zombie->setPos(x,y);
    scene->addItem(zombie);
}

void PlantGame::setCardsOpacity()
{
    if(amoutOfSun >= 50){
        PeaShooterCard->setOpacity(1.0);
        if(amoutOfSun>=100){
            TwoPeaShooterCard->setOpacity(1.0);
            WalnutCard->setOpacity(1.0);
            if(amoutOfSun >= 125){
                BoomerangCard->setOpacity(1.0);
                if(amoutOfSun>=150){
                    JalapenoCard->setOpacity(1.0);
                    if(amoutOfSun>=175)
                        PlumMineCard->setOpacity(1.0);
                }
            }
        }
    }
}


void PlantGame::getOrderOfClient(QString order)
{
    QStringList orderParts = order.split("|");
    if(orderParts[0] == "Emoji"){
        if(orderParts[1] == "Laugh"){
            Emoji* laugh = new Emoji(Emoji::EmojiType::Laugh);
            laugh->setPos(609,55); scene->addItem(laugh);
            laugh->setScale(0.15);
        }else if(orderParts[1] == "Rage"){
            Emoji* rage = new Emoji(Emoji::EmojiType::Rage);
            rage->setPos(622,63); scene->addItem(rage);
            rage->setScale(0.11);
        }
        else if(orderParts[1] == "SunGlass"){
            Emoji* sunglass = new Emoji(Emoji::EmojiType::SunGlass);
            sunglass->setPos(614,60); scene->addItem(sunglass);
            sunglass->setScale(0.13);
        }
        else if(orderParts[1] == "Poker"){
            Emoji* poker = new Emoji(Emoji::EmojiType::Poker);
            poker->setPos(635,64); scene->addItem(poker);
            poker->setScale(0.08);
        }
    }else if(orderParts[0] == "Round1Finished" || orderParts[0] == "Round2Finished"){
        view->close();
        delete this;
        return;
    }
    else if(orderParts[0]=="SPAWNAstronaut")
            spawnZombie(Zombie::ZombieType::Astronaut,orderParts[1].toInt(),orderParts[2].toInt());
    else if(orderParts[0]=="SPAWNBucketHead")
            spawnZombie(Zombie::ZombieType::BucketHead,orderParts[1].toInt(),orderParts[2].toInt());
    else if(orderParts[0]=="SPAWNPurpleHair")
           spawnZombie(Zombie::ZombieType::PurpleHair,orderParts[1].toInt(),orderParts[2].toInt());
    else if(orderParts[0]=="SPAWNTall")
           spawnZombie(Zombie::ZombieType::Tall,orderParts[1].toInt(),orderParts[2].toInt());
    else if(orderParts[0]=="SPAWNLeafHead")
           spawnZombie(Zombie::ZombieType::LeafHead,orderParts[1].toInt(),orderParts[2].toInt());
    else if(orderParts[0]=="SPAWNRegular")
            spawnZombie(Zombie::ZombieType::Regular,orderParts[1].toInt(),orderParts[2].toInt());
}

void PlantGame::updateStatus()
{
    if(secondsRemaining <=0){
        QSoundEffect* Sound = new QSoundEffect();
        Sound->setSource(QUrl::fromLocalFile(":/audio/PlantWon.wav"));
        Sound->setVolume(0.5);
        Sound->play();
        player->sendMessage("Round"+QString::number(player->currentRoundNumber)+"Finished|"+player->username);
    }
    secondsRemaining--;
    QString min = QString::number(secondsRemaining / 60);
    QString sec = QString::number(secondsRemaining % 60);
    roundTimerItem->setPlainText("Plant Side\nRemaining Time : " + min + ":" + sec+"\nSuns:"+QString::number(amoutOfSun));
}

void PlantGame::addSourceToScene()
{
    Resource* sun = new Resource(Resource::ResourceType::Sun);
    srand(time(NULL));
    int x = rand() % static_cast<int>(scene->sceneRect().width()-120);
    int y = rand() % static_cast<int>(scene->sceneRect().height()-100);
    sun->setPos(x+120,y+100);
    scene->addItem(sun);
    connect(sun,SIGNAL(collected()),this,SLOT(collectResource()));
}

void PlantGame::collectResource()
{
    QSoundEffect* Sound = new QSoundEffect();
    Sound->setSource(QUrl::fromLocalFile(":/audio/Collecting Sun.wav"));
    Sound->setVolume(0.5);
    Sound->play();
    amoutOfSun += 25;
    setCardsOpacity();
}

void PlantGame::setSelectedCart(PlantCard *selectedcard)
{
    if(selectedcard->price > amoutOfSun){
        QSoundEffect* Sound = new QSoundEffect();
        Sound->setSource(QUrl::fromLocalFile(":/audio/BuyError.wav"));
        Sound->setVolume(0.5);
        Sound->play();
        qDebug() << "Not Enough Sun for this item";
        return;
    }
    selectedCard = selectedcard;
    qDebug() << "Card Selected";
}

void PlantGame::clicked(QPointF clickedplace)
{
    int cardprice;
    QString order;
    if(selectedCard){
        cardprice = selectedCard->price;
        Plant* newplant;
        if(selectedCard->type == PlantCard::PlantCardType::PeaShooter){
            newplant = new Plant(Plant::PlantType::PeaShooter);
            order="SPAWNPeaShooter";
        }else if(selectedCard->type == PlantCard::PlantCardType::TwoPeaShooter){
            newplant = new Plant(Plant::PlantType::TwoPeaShooter);
            order="SPAWNTwoPeaShooter";
        }
        else if(selectedCard->type == PlantCard::PlantCardType::Walnut){
            newplant = new Plant(Plant::PlantType::Walnut);
            order="SPAWNWalnut";
        }
        else if(selectedCard->type == PlantCard::PlantCardType::Boomerang){
            newplant = new Plant(Plant::PlantType::Boomerang);
            order="SPAWNBoomerang";
        }
        else if(selectedCard->type == PlantCard::PlantCardType::Jalapeno){
            newplant = new Plant(Plant::PlantType::Jalapeno);
            order="SPAWNJalapeno";
        }
        else if(selectedCard->type == PlantCard::PlantCardType::PlumMine){
            newplant = new Plant(Plant::PlantType::PlumMine);
            order="SPAWNPlumMine";
        }
        int x = clickedplace.x(),y=clickedplace.y();
        if(x >= 466 || y <=40){
            qDebug() << "Can't Plant in this erea";
            delete newplant;
            return;
        }
        for(int i = 0 ; i <= 846; i+=79){
            if(i <= x && x <= (i + 79)){
                x=i; break;
            }
        }
        for(int i = 40 ; i <= 465; i+=72){
            if(i <= y && y <= (i + 72)){
                y=i; break;
            }
        }
        x+=130; y+=98;
        QPointF place(x,y);
        bool exist = false;
        for(QPointF t : planted){
            if(t == place){
                exist = true;
                break;
            }
        }
        if(exist){
            delete newplant; return;
        }
        if(newplant->Type != Plant::PlantType::Jalapeno && newplant->Type != Plant::PlantType::PlumMine)
            planted.push_back(place);
        amoutOfSun -= cardprice;
        newplant->setPos(place);
        scene->addItem(newplant);
        player->sendMessage(order+"|"+QString::number(x)+"|"+QString::number(y));
        selectedCard=nullptr;
        setCardsOpacity();
    }
}

void PlantGame::sendEmoji(Emoji *emoji)
{
    if(emoji->type == Emoji::EmojiType::Laugh)
        player->sendMessage("Emoji|Laugh");
    else if(emoji->type == Emoji::EmojiType::Rage)
        player->sendMessage("Emoji|Rage");
    else if(emoji->type == Emoji::EmojiType::SunGlass)
        player->sendMessage("Emoji|SunGlass");
    else if(emoji->type == Emoji::EmojiType::Poker)
        player->sendMessage("Emoji|Poker");
}
