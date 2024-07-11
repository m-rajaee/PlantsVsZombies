#include "client.h"
#include <QTextStream>
#include <QDebug>
#include<QDateTime>
#include "plantgame.h"
#include "zombiegame.h"
Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this))
{
    numberOfWins = 0;
    currentRoundNumber = 1;
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this,SIGNAL(Order(QString)),this,SLOT(getOrder(QString)));
}

bool Client::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
    bool IsConnected = socket->waitForConnected(1000);
    if (IsConnected)
        qDebug() << "Connected to server!";
    else
        qDebug() << "Connection failed!";
    return IsConnected;
}

void Client::registerUser(const QString &username, const QString &password, const QString &name, const QString &phone, const QString &email)
{
    if (isConnectedToServer()) {
        QTextStream stream(socket);
        stream << "REGISTER|" << username << "|" << password << "|" << name << "|" << phone << "|" << email;
        socket->flush();
    }
}

void Client::loginUser(const QString &username, const QString &password)
{
    if (isConnectedToServer()) {
        QTextStream stream(socket);
        stream << "LOGIN|" << username << "|" << password;
        socket->flush();
    }
}

void Client::resetPassword(const QString &phone, const QString &newPassword)
{
    if (isConnectedToServer()) {
        QTextStream stream(socket);
        stream << "RESET_PASSWORD|" << phone << "|" << newPassword;
        socket->flush();
    }
}

void Client::addHistory(const QString& username,const QString& opponent,const QString& role1,const QString& winner1,const QString& role2,const QString& winner2,const QString& winner)
{
    if (isConnectedToServer()) {
        QTextStream stream(socket);
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd,hh:mm:ss");
        stream << "ADD_HISTORY|" << username << "|" << opponent << "|" << time << "|" << role1 << "|" << winner1 << "|" << role2 << "|" << winner2 << "|" << winner;
        socket->flush();
    }
}

void Client::changeInformation(const QString &username, const QString &newusername, const QString &newpassword, const QString &newname, const QString &newphone, const QString &newemail)
{
    if (isConnectedToServer()) {
        QTextStream stream(socket);
        stream << "CHANGE_INFORMATION|" << username << "|" << newusername << "|" << newpassword << "|" << newname << "|" << newphone << "|" << newemail;
        socket->flush();
    }
}

void Client::showHistory(const QString& username)
{
    if (isConnectedToServer()) {
        QTextStream stream(socket);
        stream << "SHOW_HISTORY|" << username ;
        socket->flush();
    }
}

void Client::sendMessage(const QString &message)
{

    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << message;
        socket->flush();
        qDebug() << "Message sent to server:" << message;
    } else {
        qDebug() << "Not connected to server!";
    }
}

bool Client::isConnectedToServer()
{
    return (socket->state() == QTcpSocket::ConnectedState);
}

void Client::onReadyRead()
{
    QTextStream stream(socket);
    QString response = stream.readAll();
    emit Order(response);
}

void Client::getOrder(QString order)
{
    qDebug() << "Server Said : " << order;
    QStringList orderParts = order.split("|");
    if(orderParts[0] == "Loggedin"){
        username = orderParts[1];
    }else if(orderParts[0] == "InformationChanged"){
        username = orderParts[1];
    }else if(orderParts[0] == "StartTheMatch"){
        if(orderParts[1] == "Plant"){
            data.roleInRound1 = "Plant"; data.roleInRound1 = "Zombie";
            PlantGame * plantgame = new PlantGame(this);
        }else if(orderParts[1] == "Zombie"){
            data.roleInRound1 = "Zombie"; data.roleInRound1 = "Plant";
            ZombieGame* zombiegame = new ZombieGame(this);
        }
    }else if(orderParts[0] == "Round1Finished"){
        currentRoundNumber++;
        data.winnerOfRound1 = orderParts[1];
        if(data.winnerOfRound1 == username)
            numberOfWins++;
        if(data.roleInRound1 == "Zombie")
            ZombieGame* zombiegame = new ZombieGame(this);
        else if(data.roleInRound1 == "Plant")
            PlantGame * plantgame = new PlantGame(this);
    }else if(orderParts[0] == "Round2Finished"){
        data.winnerOfRound2 = orderParts[1];
        if(data.winnerOfRound2 == username)
            numberOfWins++;
        if(numberOfWins == 0)
            data.winnerOfTheMatch = data.oponnent;
        else if(numberOfWins == 1)
            data.winnerOfTheMatch = "Draw";
        else if(numberOfWins ==2)
            data.winnerOfTheMatch = username;
        addHistory(username,data.oponnent,data.roleInRound1,data.winnerOfRound1,data.roleInRound1,data.winnerOfRound2,data.winnerOfTheMatch);
        numberOfWins = 0; currentRoundNumber = 1;
        emit matchFinished();
    }
}


