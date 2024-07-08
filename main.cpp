#include "Authorization.h"
#include "server.h"
#include <QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server;
    Client Player1, Player2;
    Player1.connectToServer("127.0.0.1",12345); Player2.connectToServer("127.0.0.1",12345);
    Authorization page1(&Player1);
    page1.show();
    Authorization page2(&Player2);
    page2.show();
    return a.exec();
}
