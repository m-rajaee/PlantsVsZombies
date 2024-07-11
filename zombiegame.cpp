#include "zombiegame.h"
#include "emoji.h"
#include<QGraphicsItem>
#include <QSoundEffect>
ZombieGame::ZombieGame(Client* c) {
    QSoundEffect* Sound = new QSoundEffect();
    Sound->setSource(QUrl::fromLocalFile(":/audio/Playing.wav"));
    Sound->setVolume(0.02);
    Sound->play();
    amountOfBrain = 0;
    secondsRemaining = 210;
    player = c;
    selectedCard = nullptr;
    QTimer* resourceTimer = new QTimer();
    connect(resourceTimer,SIGNAL(timeout()),this,SLOT(addResource()));
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
    //Adding Round Timer
    QTimer* RoundTimer = new QTimer();
    roundTimerItem = new QGraphicsTextItem();
    roundTimerItem->setDefaultTextColor(Qt::yellow);
    roundTimerItem->setFont(QFont("Arial",16));
    connect(RoundTimer,SIGNAL(timeout()),this,SLOT(updateStatus()));
    RoundTimer->start(1000); // Update every second
    scene->addItem(roundTimerItem);
    roundTimerItem->setPos(scene->sceneRect().width() - 230 ,10);
    //Adding Cards To scene
    BucketHeadCard = new ZombieCard(ZombieCard::ZombieCardType::BucketHead);
    BucketHeadCard->setPos(10,10); scene->addItem(BucketHeadCard);
    PurpleHairCard = new ZombieCard(ZombieCard::ZombieCardType::PurpleHair);
    PurpleHairCard->setPos(110,10); scene->addItem(PurpleHairCard);
    RegularCard = new ZombieCard(ZombieCard::ZombieCardType::Regular);
    RegularCard->setPos(210,10); scene->addItem(RegularCard);
    TallCard = new ZombieCard(ZombieCard::ZombieCardType::Tall);
    TallCard->setPos(310,10); scene->addItem(TallCard);
    LeafHeadCard = new ZombieCard(ZombieCard::ZombieCardType::LeafHead);
    LeafHeadCard->setPos(410,10); scene->addItem(LeafHeadCard);
    AstronautCard = new ZombieCard(ZombieCard::ZombieCardType::Astronaut);
    AstronautCard->setPos(510,10); scene->addItem(AstronautCard);
    connect(BucketHeadCard,SIGNAL(selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));
    connect(PurpleHairCard,SIGNAL(selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));
    connect(RegularCard,SIGNAL(selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));
    connect(TallCard,SIGNAL(selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));
    connect(LeafHeadCard,SIGNAL(selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));
    connect(AstronautCard,SIGNAL(selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));
    // Show Prices
    QGraphicsTextItem* BucketHeadCardPrice = new QGraphicsTextItem();
    QGraphicsTextItem* PurpleHairCardPrice = new QGraphicsTextItem();
    QGraphicsTextItem* RegularCardPrice = new QGraphicsTextItem();
    QGraphicsTextItem* TallCardPrice = new QGraphicsTextItem();
    QGraphicsTextItem* LeafHeadCardPrice = new QGraphicsTextItem();
    QGraphicsTextItem* AstronautCardPrice = new QGraphicsTextItem();
    BucketHeadCardPrice->setDefaultTextColor(Qt::yellow);
    BucketHeadCardPrice->setFont(QFont("Arial",12));BucketHeadCardPrice->setPlainText("200"); BucketHeadCardPrice->setPos(25,80); scene->addItem(BucketHeadCardPrice);
    PurpleHairCardPrice->setDefaultTextColor(Qt::yellow);
    PurpleHairCardPrice->setFont(QFont("Arial",12));PurpleHairCardPrice->setPlainText("800"); PurpleHairCardPrice->setPos(125,80); scene->addItem(PurpleHairCardPrice);
    RegularCardPrice->setDefaultTextColor(Qt::yellow);
    RegularCardPrice->setFont(QFont("Arial",12));RegularCardPrice->setPlainText("100"); RegularCardPrice->setPos(225,80); scene->addItem(RegularCardPrice);
    TallCardPrice->setDefaultTextColor(Qt::yellow);
    TallCardPrice->setFont(QFont("Arial",12));TallCardPrice->setPlainText("150"); TallCardPrice->setPos(325,80); scene->addItem(TallCardPrice);
    LeafHeadCardPrice->setDefaultTextColor(Qt::yellow);
    LeafHeadCardPrice->setFont(QFont("Arial",12));LeafHeadCardPrice->setPlainText("150"); LeafHeadCardPrice->setPos(425,80); scene->addItem(LeafHeadCardPrice);
    AstronautCardPrice->setDefaultTextColor(Qt::yellow);
    AstronautCardPrice->setFont(QFont("Arial",12));AstronautCardPrice->setPlainText("200"); AstronautCardPrice->setPos(525,80); scene->addItem(AstronautCardPrice);
    //Show Username
    QGraphicsTextItem* username = new QGraphicsTextItem();
    username->setFont(QFont("Arial",16));username->setPlainText(player->username); username->setPos(590,3); scene->addItem(username);
    username->setDefaultTextColor(Qt::darkCyan);
    //Adding Emojes
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

void ZombieGame::spawnPlant(Plant::PlantType type,int x , int y)
{
    Plant* plant = new Plant(type);
    plant->setPos(x,y);
    scene->addItem(plant);
}
void ZombieGame::getOrderOfClient(QString order)
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
    else if(orderParts[0]=="SPAWNPeaShooter")
        spawnPlant(Plant::PlantType::PeaShooter,orderParts[1].toInt(),orderParts[2].toInt());
    else if(orderParts[0]=="SPAWNTwoPeaShooter")
        spawnPlant(Plant::PlantType::TwoPeaShooter,orderParts[1].toInt(),orderParts[2].toInt());
    else if(orderParts[0]=="SPAWNWalnut")
        spawnPlant(Plant::PlantType::Walnut,orderParts[1].toInt(),orderParts[2].toInt());
    else if(orderParts[0]=="SPAWNPlumMine")
        spawnPlant(Plant::PlantType::PlumMine,orderParts[1].toInt(),orderParts[2].toInt());
    else if(orderParts[0]=="SPAWNJalapeno")
        spawnPlant(Plant::PlantType::Jalapeno,orderParts[1].toInt(),orderParts[2].toInt());
    else if(orderParts[0]=="SPAWNBoomerang")
        spawnPlant(Plant::PlantType::Boomerang,orderParts[1].toInt(),orderParts[2].toInt());
}
void ZombieGame::updateStatus()
{
    secondsRemaining--;
    QString min = QString::number(secondsRemaining / 60);
    QString sec = QString::number(secondsRemaining % 60);
    roundTimerItem->setPlainText("Zombie Side\nRemaining Time : " + min + ":" + sec + "\nBrains : "+QString::number(amountOfBrain));
}

void ZombieGame::addResource()
{
    Resource* brain = new Resource(Resource::ResourceType::Brain);
    int x = rand() % static_cast<int>(scene->sceneRect().width()-120);
    int y = rand() % static_cast<int>(scene->sceneRect().height()-100);
    brain->setPos(x+120, y+100);
    scene->addItem(brain);
    connect(brain,SIGNAL(collected()),this,SLOT(collectResource()));
}

void ZombieGame::collectResource()
{
    amountOfBrain += 25;
    setCardsOpacity();
}

void ZombieGame::won()
{
    QSoundEffect* Sound = new QSoundEffect();
    Sound->setSource(QUrl::fromLocalFile(":/audio/ZombieWon.wav"));
    Sound->setVolume(0.5);
    Sound->play();
    player->sendMessage("Round"+QString::number(player->currentRoundNumber)+"Finished|"+player->username);
}

void ZombieGame::setSelectedCart(ZombieCard *selectedcard)
{
    if(selectedcard->price > amountOfBrain){
        QSoundEffect* Sound = new QSoundEffect();
        Sound->setSource(QUrl::fromLocalFile(":/audio/BuyError.wav"));
        Sound->setVolume(0.5);
        Sound->play();
        qDebug() << "Not Enouth Brain for this item";
        return;
    }
    selectedCard = selectedcard;
    qDebug() << "Card Selected";
 }

void ZombieGame::clicked(QPointF clickedplace)
{
    qDebug() << clickedplace;
    int cardprice;
    QString order;
    if(selectedCard){
        cardprice = selectedCard->price;
        Zombie* newzombie;
        if(selectedCard->type == ZombieCard::ZombieCardType::BucketHead){
            newzombie = new Zombie(Zombie::ZombieType::BucketHead);
            order = "SPAWNBucketHead";
        }else if(selectedCard->type == ZombieCard::ZombieCardType::Astronaut){
            newzombie = new Zombie(Zombie::ZombieType::Astronaut);
            order = "SPAWNAstronaut";
        }
        else if(selectedCard->type == ZombieCard::ZombieCardType::LeafHead){
            newzombie = new Zombie(Zombie::ZombieType::LeafHead);
            order = "SPAWNLeafHead";
        }
        else if(selectedCard->type == ZombieCard::ZombieCardType::Regular){
            newzombie = new Zombie(Zombie::ZombieType::Regular);
            order = "SPAWNRegular";
        }
        else if(selectedCard->type == ZombieCard::ZombieCardType::PurpleHair){
            newzombie = new Zombie(Zombie::ZombieType::PurpleHair);
            order = "SPAWNPurpleHair";
        }
        else if(selectedCard->type == ZombieCard::ZombieCardType::Tall){
            newzombie = new Zombie(Zombie::ZombieType::Tall);
            order = "SPAWNTall";
        }
        int x = clickedplace.x(),y=clickedplace.y();
        if(x <= 775 || y <=40){
            qDebug() << "Zombies should be putt in last column";
            delete newzombie;
            return;
        }
        x = 790;
        for(int i = 40 ; i <= 465; i+=72){
            if(i <= y && y <= (i + 72)){
                y=i; break;
            }
        }
        x+=100; y+=87;
        player->sendMessage(order+"|"+QString::number(x)+"|"+QString::number(y));
        QPointF place(x,y);
        amountOfBrain -= cardprice;
        newzombie->setPos(place);
        scene->addItem(newzombie);
        selectedCard=nullptr;
        connect(newzombie,SIGNAL(zombieWon()),this,SLOT(won()));
        setCardsOpacity();
    }
}

void ZombieGame::sendEmoji(Emoji *emoji)
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

void ZombieGame::setCardsOpacity()
{
    if(amountOfBrain >= 100){
        RegularCard->setOpacity(1.0);
        if(amountOfBrain>=150){
            LeafHeadCard->setOpacity(1.0);
            TallCard->setOpacity(1.0);
            if(amountOfBrain >= 200){
                BucketHeadCard->setOpacity(1.0);
                AstronautCard->setOpacity(1.0);
                    if(amountOfBrain >= 800)
                        PurpleHairCard->setOpacity(1.0);
                }
            }
        }
}
