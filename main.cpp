#include "plantslogin.h"
#include "zombieslogin.h"
#include "server.h"
#include <QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server;
    //Client Plants_client, Zombies_client;
    //PlantsLogin plantslogin(&Plants_client);
    //plantslogin.show();
    //ZombiesLogin zombieslogin(&Zombies_client);
    //zombieslogin.show();
    Client c1,c2; c1.connectToServer("127.0.0.1",12345);c2.connectToServer("127.0.0.1",12345);
    c1.SendMessage("Message From Client 1");
    return a.exec();
}
