#include "plantslogin.h"
#include "zombieslogin.h"
#include "server.h"
#include <QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server;
    Client Plants_client, Zombies_client;
    Plants_client.connectToServer("127.0.0.1",12345);
    //Zombies_client.connectToServer("127.0.0.1",12345);
    PlantsLogin plantslogin(&Plants_client);
    plantslogin.show();
    //ZombiesLogin zombieslogin(&Zombies_client);
    //zombieslogin.show();
    return a.exec();
}
