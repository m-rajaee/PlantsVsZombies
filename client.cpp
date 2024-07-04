#include "client.h"
#include <QTextStream>
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
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
        stream << "REGISTER " << username << " " << password << " " << name << " " << phone << " " << email << "\n";
        socket->flush();
    }
}

void Client::loginUser(const QString &username, const QString &password)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << "LOGIN " << username << " " << password << "\n";
        socket->flush();
    }
}

void Client::resetPassword(const QString &phone, const QString &newPassword)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QTextStream stream(socket);
        stream << "RESET_PASSWORD " << phone << " " << newPassword << "\n";
        socket->flush();
    }
}

void Client::onReadyRead()
{
    QTextStream stream(socket);
    QString response = stream.readAll();
    qDebug() << "Server response:" << response;
}