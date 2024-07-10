#include "Authorization.h"
#include "server.h"
#include "start.h"
#include <QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server;
    Client Player1, Player2;
    Start start1(&Player1);
    start1.show();
    Start start2(&Player2);
    start2.show();
    //Authorization page1(&Player1);
    //page1.show();
    //Authorization page2(&Player2);
    //page2.show();
    return a.exec();
}
