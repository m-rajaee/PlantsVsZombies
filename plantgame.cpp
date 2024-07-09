#include "plantgame.h"
#include "mouse.h"
#include<QGraphicsItem>
PlantGame::PlantGame(Client* c) {
    seconds = 210;
    sun = 0;
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

    view->show(); //Showing View
}

void PlantGame::spawnZombie(Zombie::ZombieType type, int x, int y)
{
    Zombie* zombie = new Zombie(type);
    zombie->setPos(x,y);
    scene->addItem(zombie);
}


void PlantGame::GetOrderOfClient(QString order)
{
    QStringList parts = order.split("|");
    if(parts[0] == "Round1Finished" || parts[0] == "Round2Finished"){
        this->close();
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
        player->SendMessage("Round"+QString::number(player->round)+"Finished|"+player->Username);
        this->close();
        delete this;
        return;
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
    sun += 25;
}

void PlantGame::setSelectedCart(PlantCard *selectedcard)
{
    if(selectedcard->price > sun){
        qDebug() << "Not Enouth Sun for this item";
        return;
    }
    SelectedCard = selectedcard;
    qDebug() << "cArd Selected";
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
        x+=130; y+=100;
        player->SendMessage(order+"|"+QString::number(x)+"|"+QString::number(y));
        QPointF place(x,y);
        sun -= cardprice;
        newplant->setPos(place);
        scene->addItem(newplant);
        SelectedCard=nullptr;
    }
}
