#include "client.h"
#include <QTextStream>
#include <QDebug>
#include<QDateTime>
Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(this,SIGNAL(Order(QString)),this,SLOT(getOrder(QString)));
}

void Client::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
    if (socket->waitForConnected(1000)) {
        qDebug() << "Connected to server!";
    } else {
        qDebug() << "Connection failed!";
    }
}

void Client::registerUser(const QString &username, const QString &password, const QString &name, const QString &phone, const QString &email)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << "REGISTER " << username << " " << password << " " << name << " " << phone << " " << email;
        socket->flush();
    }
}

void Client::loginUser(const QString &username, const QString &password)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << "LOGIN " << username << " " << password;
        socket->flush();
    }
}

void Client::resetPassword(const QString &phone, const QString &newPassword)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << "RESET_PASSWORD " << phone << " " << newPassword;
        socket->flush();
    }
}

void Client::addHistory(const QString& username,const QString& harif, const QString& role, const QString& winner)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd,hh:mm:ss");
        stream << "ADD_HISTORY " << username << " " << harif << " " << time << " " << role << " " << winner;
        socket->flush();
    }
}

void Client::ChangeInformation(const QString &username, const QString &newusername, const QString &newpassword, const QString &newname, const QString &newphone, const QString &newemail)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << "CHANGE_INFORMATION " << username << " " << newusername << " " << newpassword << " " << newname << " " << newphone << " " << newemail;
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
    }
}


