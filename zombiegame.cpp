#include "zombiegame.h"
#include<QGraphicsItem>
ZombieGame::ZombieGame(Client* c) {
    brain = 0;
    seconds = 210;
    player = c;
    SelectedCard = nullptr;
    QTimer* ResourceTimer = new QTimer();
    connect(ResourceTimer,SIGNAL(timeout()),this,SLOT(AddSource()));
    ResourceTimer->start(5000);
    connect(player,SIGNAL(Order(QString)),this,SLOT(GetOrderOfClient(QString)));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    //Player* player = new Player();
    //status = new Status(player);
    //scene->addItem(status);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(970,580);
    scene->setSceneRect(0,0,970,580);
    //scene->addItem(player);
    //player->setPos(scene->sceneRect().width()/2,100);
    view->setBackgroundBrush(QBrush(QImage(":/image/filed.png")));
    //Adding Mouse Control
    Mouse* mouse = new Mouse(); mouse->setPos(120,100);
    scene->addItem(mouse);
    connect(mouse,SIGNAL(clicked(QPointF)),this,SLOT(clicked(QPointF)));
    //Adding Round Timer
    QTimer* RoundTimer = new QTimer();
    RoundTimerItem = new QGraphicsTextItem();
    RoundTimerItem->setDefaultTextColor(Qt::yellow);
    RoundTimerItem->setFont(QFont("Arial",16));
    connect(RoundTimer,SIGNAL(timeout()),this,SLOT(UpdateStatus()));
    RoundTimer->start(1000); // Update every second
    scene->addItem(RoundTimerItem);
    RoundTimerItem->setPos(scene->sceneRect().width() - 230 ,10);
    //Adding Cards To scene
    ZombieCard* BucketHeadCard = new ZombieCard(ZombieCard::ZombieCardType::BucketHead);
    BucketHeadCard->setPos(10,10); scene->addItem(BucketHeadCard);
    ZombieCard* PurpleHairCard = new ZombieCard(ZombieCard::ZombieCardType::PurpleHair);
    PurpleHairCard->setPos(110,10); scene->addItem(PurpleHairCard);
    ZombieCard* RegularCard = new ZombieCard(ZombieCard::ZombieCardType::Regular);
    RegularCard->setPos(210,10); scene->addItem(RegularCard);
    ZombieCard* TallCard = new ZombieCard(ZombieCard::ZombieCardType::Tall);
    TallCard->setPos(310,10); scene->addItem(TallCard);
    ZombieCard* LeafHeadCard = new ZombieCard(ZombieCard::ZombieCardType::LeafHead);
    LeafHeadCard->setPos(410,10); scene->addItem(LeafHeadCard);
    ZombieCard* AstronautCard = new ZombieCard(ZombieCard::ZombieCardType::Astronaut);
    AstronautCard->setPos(510,10); scene->addItem(AstronautCard);
    connect(BucketHeadCard,SIGNAL(Selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));
    connect(PurpleHairCard,SIGNAL(Selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));
    connect(RegularCard,SIGNAL(Selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));
    connect(TallCard,SIGNAL(Selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));
    connect(LeafHeadCard,SIGNAL(Selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));
    connect(AstronautCard,SIGNAL(Selected(ZombieCard*)),this,SLOT(setSelectedCart(ZombieCard*)));

    view->show(); //Showing View
}

void ZombieGame::spawnPlant(Plant::PlantType type,int x , int y)
{
    Plant* plant = new Plant(type);
    plant->setPos(x,y);
    scene->addItem(plant);
}
void ZombieGame::GetOrderOfClient(QString order)
{
    QStringList parts = order.split("|");
    if(parts[0] == "Round1Finished" || parts[0] == "Round2Finished"){
        this->close();
        delete this;
        return;
    }
    else if(parts[0]=="SPAWNPeaShooter")
        spawnPlant(Plant::PlantType::PeaShooter,parts[1].toInt(),parts[2].toInt());
    else if(parts[0]=="SPAWNTwoPeaShooter")
        spawnPlant(Plant::PlantType::TwoPeaShooter,parts[1].toInt(),parts[2].toInt());
    else if(parts[0]=="SPAWNWalnut")
        spawnPlant(Plant::PlantType::Walnut,parts[1].toInt(),parts[2].toInt());
    else if(parts[0]=="SPAWNPlumMine")
        spawnPlant(Plant::PlantType::PlumMine,parts[1].toInt(),parts[2].toInt());
    else if(parts[0]=="SPAWNJalapeno")
        spawnPlant(Plant::PlantType::Jalapeno,parts[1].toInt(),parts[2].toInt());
    else if(parts[0]=="SPAWNBoomerang")
        spawnPlant(Plant::PlantType::Boomerang,parts[1].toInt(),parts[2].toInt());
}

void ZombieGame::UpdateStatus()
{
    seconds--;
    QString min = QString::number(seconds / 60);
    QString sec = QString::number(seconds % 60);
    RoundTimerItem->setPlainText("Zombie Side\nRemaining Time : " + min + ":" + sec + "\nBrains : "+QString::number(brain));
}

void ZombieGame::AddSource()
{
    Resource* brain = new Resource(Resource::ResourceType::Brain);
    int x = rand() % static_cast<int>(scene->sceneRect().width()-120);
    int y = rand() % static_cast<int>(scene->sceneRect().height()-100);
    brain->setPos(x+120, y+100);
    scene->addItem(brain);
    connect(brain,SIGNAL(Collected()),this,SLOT(CollectResource()));
}

void ZombieGame::CollectResource()
{
    brain += 25;
}

void ZombieGame::Won()
{
    player->SendMessage("Round"+QString::number(player->round)+"Finished|"+player->Username);
    this->close();
    delete this;
}

void ZombieGame::setSelectedCart(ZombieCard *selectedcard)
{
    if(selectedcard->price > brain){
        qDebug() << "Not Enouth Brain for this item";
        return;
    }
    SelectedCard = selectedcard;
    qDebug() << "cArd Selected";
 }

void ZombieGame::clicked(QPointF clickedplace)
{
    int cardprice;
    QString order;
    if(SelectedCard){
        cardprice = SelectedCard->price;
        Zombie* newzombie;
        if(SelectedCard->type == ZombieCard::ZombieCardType::BucketHead){
            newzombie = new Zombie(Zombie::ZombieType::BucketHead);
            order = "SPAWNBucketHead";
        }else if(SelectedCard->type == ZombieCard::ZombieCardType::Astronaut){
            newzombie = new Zombie(Zombie::ZombieType::Astronaut);
            order = "SPAWNAstronaut";
        }
        else if(SelectedCard->type == ZombieCard::ZombieCardType::LeafHead){
            newzombie = new Zombie(Zombie::ZombieType::LeafHead);
            order = "SPAWNLeafHead";
        }
        else if(SelectedCard->type == ZombieCard::ZombieCardType::Regular){
            newzombie = new Zombie(Zombie::ZombieType::Regular);
            order = "SPAWNRegular";
        }
        else if(SelectedCard->type == ZombieCard::ZombieCardType::PurpleHair){
            newzombie = new Zombie(Zombie::ZombieType::PurpleHair);
            order = "SPAWNPurpleHair";
        }
        else if(SelectedCard->type == ZombieCard::ZombieCardType::Tall){
            newzombie = new Zombie(Zombie::ZombieType::Tall);
            order = "SPAWNTall";
        }
        int x = clickedplace.x(),y=clickedplace.y();
        if(x <= 775 || y <=40){
            qDebug() << "Zombies should be putt in last column";
            delete newzombie;
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
        x+=130; y+=100;
        player->SendMessage(order+"|"+QString::number(x)+"|"+QString::number(y));
        QPointF place(x,y);
        brain -= cardprice;
        newzombie->setPos(place);
        scene->addItem(newzombie);
        SelectedCard=nullptr;
        connect(newzombie,SIGNAL(zombieWon()),this,SLOT(Won()));
    }
}
