#include "plantgame.h"
#include "mouse.h"
#include<QGraphicsItem>
#include <QSoundEffect>
PlantGame::PlantGame(Client* c) {
    QSoundEffect* Sound = new QSoundEffect();
    Sound->setSource(QUrl::fromLocalFile(":/audio/Playing.wav"));
    Sound->setVolume(0.2);
    Sound->play();
    seconds = 210;
    sun = 2000;
    player = c;
    SelectedCard=nullptr;
    QTimer* ResourceTimer = new QTimer();
    connect(ResourceTimer,SIGNAL(timeout()),this,SLOT(AddSource()));
    ResourceTimer->start(5000);
    connect(player,SIGNAL(Order(QString)),this,SLOT(GetOrderOfClient(QString)));
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
    RoundTimerItem = new QGraphicsTextItem();
    RoundTimerItem->setDefaultTextColor(Qt::yellow);
    RoundTimerItem->setFont(QFont("Arial",16));
    connect(RoundTimer,SIGNAL(timeout()),this,SLOT(UpdateStatus()));
    RoundTimer->start(1000); // Update every second
    scene->addItem(RoundTimerItem);
    RoundTimerItem->setPos(scene->sceneRect().width() - 230,10);
    //Adding Cards To scene
    PlantCard* BoomerangCard = new PlantCard(PlantCard::PlantCardType::Boomerang);
    BoomerangCard->setPos(10,10); scene->addItem(BoomerangCard);
    PlantCard* JalapenoCard = new PlantCard(PlantCard::PlantCardType::Jalapeno);
    JalapenoCard->setPos(110,10); scene->addItem(JalapenoCard);
    PlantCard* PeaShooterCard = new PlantCard(PlantCard::PlantCardType::PeaShooter);
    PeaShooterCard->setPos(210,10); scene->addItem(PeaShooterCard);
    PlantCard* PlumMineCard = new PlantCard(PlantCard::PlantCardType::PlumMine);
    PlumMineCard->setPos(310,10); scene->addItem(PlumMineCard);
    PlantCard* TwoPeaShooterCard = new PlantCard(PlantCard::PlantCardType::TwoPeaShooter);
    TwoPeaShooterCard->setPos(410,10); scene->addItem(TwoPeaShooterCard);
    PlantCard* WalnutCard = new PlantCard(PlantCard::PlantCardType::Walnut);
    WalnutCard->setPos(510,10); scene->addItem(WalnutCard);
    connect(BoomerangCard,SIGNAL(Selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
    connect(JalapenoCard,SIGNAL(Selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
    connect(PeaShooterCard,SIGNAL(Selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
    connect(PlumMineCard,SIGNAL(Selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
    connect(TwoPeaShooterCard,SIGNAL(Selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
    connect(WalnutCard,SIGNAL(Selected(PlantCard*)),this,SLOT(setSelectedCart(PlantCard*)));
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

    view->show(); //Showing View
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
    Sound->setVolume(0.4);
    Sound->play();
    Zombie* zombie = new Zombie(type);
    zombie->setPos(x,y);
    scene->addItem(zombie);
}


void PlantGame::GetOrderOfClient(QString order)
{
    QStringList parts = order.split("|");
    if(parts[0] == "Round1Finished" || parts[0] == "Round2Finished"){
        view->close();
        delete this;
        return;
    }
    else if(parts[0]=="SPAWNAstronaut")
            spawnZombie(Zombie::ZombieType::Astronaut,parts[1].toInt(),parts[2].toInt());
    else if(parts[0]=="SPAWNBucketHead")
            spawnZombie(Zombie::ZombieType::BucketHead,parts[1].toInt(),parts[2].toInt());
    else if(parts[0]=="SPAWNPurpleHair")
           spawnZombie(Zombie::ZombieType::PurpleHair,parts[1].toInt(),parts[2].toInt());
    else if(parts[0]=="SPAWNTall")
           spawnZombie(Zombie::ZombieType::Tall,parts[1].toInt(),parts[2].toInt());
    else if(parts[0]=="SPAWNLeafHead")
           spawnZombie(Zombie::ZombieType::LeafHead,parts[1].toInt(),parts[2].toInt());
    else if(parts[0]=="SPAWNRegular")
            spawnZombie(Zombie::ZombieType::Regular,parts[1].toInt(),parts[2].toInt());
}

void PlantGame::UpdateStatus()
{
    if(seconds <=0){
        QSoundEffect* Sound = new QSoundEffect();
        Sound->setSource(QUrl::fromLocalFile(":/audio/PlantWon.wav"));
        Sound->setVolume(0.4);
        Sound->play();
        player->SendMessage("Round"+QString::number(player->round)+"Finished|"+player->Username);
    }
    seconds--;
    QString min = QString::number(seconds / 60);
    QString sec = QString::number(seconds % 60);
    RoundTimerItem->setPlainText("Plant Side\nRemaining Time : " + min + ":" + sec+"\nSuns:"+QString::number(sun));
}

void PlantGame::AddSource()
{
    Resource* sun = new Resource(Resource::ResourceType::Sun);
    srand(time(NULL));
    int x = rand() % static_cast<int>(scene->sceneRect().width()-120);
    int y = rand() % static_cast<int>(scene->sceneRect().height()-100);
    sun->setPos(x+120,y+100);
    scene->addItem(sun);
    connect(sun,SIGNAL(Collected()),this,SLOT(CollectResource()));
}

void PlantGame::CollectResource()
{
    QSoundEffect* Sound = new QSoundEffect();
    Sound->setSource(QUrl::fromLocalFile(":/audio/Collecting Sun.wav"));
    Sound->setVolume(0.4);
    Sound->play();
    sun += 25;
}

void PlantGame::setSelectedCart(PlantCard *selectedcard)
{
    if(selectedcard->price > sun){
        QSoundEffect* Sound = new QSoundEffect();
        Sound->setSource(QUrl::fromLocalFile(":/audio/BuyError.wav"));
        Sound->setVolume(0.4);
        Sound->play();
        qDebug() << "Not Enough Sun for this item";
        return;
    }
    SelectedCard = selectedcard;
    qDebug() << "Card Selected";
}

void PlantGame::clicked(QPointF clickedplace)
{
    int cardprice;
    QString order;
    if(SelectedCard){
        cardprice = SelectedCard->price;
        Plant* newplant;
        if(SelectedCard->type == PlantCard::PlantCardType::PeaShooter){
            newplant = new Plant(Plant::PlantType::PeaShooter);
            order="SPAWNPeaShooter";
        }else if(SelectedCard->type == PlantCard::PlantCardType::TwoPeaShooter){
            newplant = new Plant(Plant::PlantType::TwoPeaShooter);
            order="SPAWNTwoPeaShooter";
        }
        else if(SelectedCard->type == PlantCard::PlantCardType::Walnut){
            newplant = new Plant(Plant::PlantType::Walnut);
            order="SPAWNWalnut";
        }
        else if(SelectedCard->type == PlantCard::PlantCardType::Boomerang){
            newplant = new Plant(Plant::PlantType::Boomerang);
            order="SPAWNBoomerang";
        }
        else if(SelectedCard->type == PlantCard::PlantCardType::Jalapeno){
            newplant = new Plant(Plant::PlantType::Jalapeno);
            order="SPAWNJalapeno";
        }
        else if(SelectedCard->type == PlantCard::PlantCardType::PlumMine){
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
        if(newplant->type != Plant::PlantType::Jalapeno && newplant->type != Plant::PlantType::PlumMine)
            planted.push_back(place);
        sun -= cardprice;
        newplant->setPos(place);
        scene->addItem(newplant);
        player->SendMessage(order+"|"+QString::number(x)+"|"+QString::number(y));
        SelectedCard=nullptr;
    }
}
