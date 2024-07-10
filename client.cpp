#include "client.h"
#include <QTextStream>
#include <QDebug>
#include<QDateTime>
#include "plantgame.h"
#include "zombiegame.h"
Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this))
{
    wins = 0;
    round = 1;
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(this,SIGNAL(Order(QString)),this,SLOT(getOrder(QString)));
}

bool Client::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
    if (socket->waitForConnected(1000)) {
        qDebug() << "Connected to server!";
        return true;
    } else {
        qDebug() << "Connection failed!";
        return false;
    }
}

void Client::registerUser(const QString &username, const QString &password, const QString &name, const QString &phone, const QString &email)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << "REGISTER|" << username << "|" << password << "|" << name << "|" << phone << "|" << email;
        socket->flush();
    }
}

void Client::loginUser(const QString &username, const QString &password)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << "LOGIN|" << username << "|" << password;
        socket->flush();
    }
}

void Client::resetPassword(const QString &phone, const QString &newPassword)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << "RESET_PASSWORD|" << phone << "|" << newPassword;
        socket->flush();
    }
}

void Client::addHistory(const QString& username,const QString& opponent,const QString& role1,const QString& winner1,const QString& role2,const QString& winner2,const QString& winner)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd,hh:mm:ss");
        stream << "ADD_HISTORY|" << username << "|" << opponent << "|" << time << "|" << role1 << "|" << winner1 << "|" << role2 << "|" << winner2 << "|" << winner;
        socket->flush();
    }
}

void Client::ChangeInformation(const QString &username, const QString &newusername, const QString &newpassword, const QString &newname, const QString &newphone, const QString &newemail)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << "CHANGE_INFORMATION|" << username << "|" << newusername << "|" << newpassword << "|" << newname << "|" << newphone << "|" << newemail;
        socket->flush();
    }
}

void Client::ShowHistory(const QString& username)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << "SHOW_HISTORY|" << username ;
        socket->flush();
    }
}

void Client::SendMessage(const QString &message)
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

void Client::onReadyRead()
{
    QTextStream stream(socket);
    QString response = stream.readAll();
    emit Order(response);
}

void Client::getOrder(QString order)
{
    qDebug() << "Server Said : " << order;
    QStringList parts = order.split("|");
    if(parts[0] == "Loggedin"){
        Username = parts[1];
    }else if(parts[0] == "InformationChanged"){
        Username = parts[1];
    }else if(parts[0] == "StartTheMatch"){
        if(parts[1] == "Plant"){
            data.role1 = "Plant"; data.role2 = "Zombie";
            PlantGame * plantgame = new PlantGame(this);
        }else if(parts[1] == "Zombie"){
            data.role1 = "Zombie"; data.role2 = "Plant";
            ZombieGame* zombiegame = new ZombieGame(this);
        }
    }else if(parts[0] == "Round1Finished"){
        round++;
        data.winner1 = parts[1];
        if(data.winner1 == Username)
            wins++;
        if(data.role2 == "Zombie")
            ZombieGame* zombiegame = new ZombieGame(this);
        else if(data.role2 == "Plant")
            PlantGame * plantgame = new PlantGame(this);
    }else if(parts[0] == "Round2Finished"){
        data.winner2 = parts[1];
        if(data.winner2 == Username)
            wins++;
        if(wins == 0)
            data.winner = data.opponent;
        else if(wins == 1)
            data.winner = "Draw";
        else if(wins ==2)
            data.winner = Username;
        addHistory(Username,data.opponent,data.role1,data.winner1,data.role2,data.winner2,data.winner);
        wins = 0; round = 1;
        emit MatchFinished();
    }
}


