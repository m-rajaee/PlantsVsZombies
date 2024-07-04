#include "plantslogin.h"
//#include "zombieslogin.h"
#include "server.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server;
    PlantsLogin plantslogin;
    plantslogin.show();
    //ZombiesLogin zombieslogin;
    //zombieslogin.show();
    Client c; c.connectToServer("127.0.0.1",12345);
        return a.exec();
}
