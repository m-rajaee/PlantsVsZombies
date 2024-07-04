#include "server.h"
#include <QTextStream>
#include <QDebug>
#include <QCryptographicHash>

Server::Server(QObject *parent) : QTcpServer(parent)
{
    loadUserData();
    if (this->listen(QHostAddress::Any, 12345)) {
        qDebug() << "Server started!";
    } else {
        qDebug() << "Server could not start!";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    if (socket->setSocketDescriptor(socketDescriptor)) {
        connect(socket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &Server::onDisconnected);
        clients[socket] = "";
        qDebug() << "New client connected!";
    } else {
        delete socket;
    }
}

void Server::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        QTextStream stream(socket);
        QString request = stream.readAll();
        processRequest(socket, request);
    }
}

void Server::onDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        clients.remove(socket);
        socket->deleteLater();
        qDebug() << "Client disconnected!";
    }
}

void Server::loadUserData()
{
    QFile file("D:/Qt/temp2ofproject/users.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        users = doc.object().value("users").toArray();
        file.close();
    }
}

void Server::saveUserData()
{
    QFile file("D:/Qt/temp2ofproject/users.json");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject obj;
        obj["users"] = users;
        QJsonDocument doc(obj);
        file.write(doc.toJson());
        file.close();
    }
}

QString Server::hashPassword(const QString &password)
{
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

void Server::processRequest(QTcpSocket *socket, const QString &request)
{
    QTextStream stream(socket);
    QStringList parts = request.split(" ");
    if (parts.isEmpty()) {
        stream << "Invalid request\n";
        return;
    }

    QString command = parts[0].toUpper();
    if (command == "REGISTER") {
        if (parts.size() != 6) {
            stream << "Invalid parameters\n";
            return;
        }
        QString username = parts[1];
        QString password = parts[2];
        QString name = parts[3];
        QString phone = parts[4];
        QString email = parts[5];

        QJsonObject obj;
        obj["username"] = username;
        obj["password"] = hashPassword(password);
        obj["name"] = name;
        obj["phone"] = phone;
        obj["email"] = email;

        users.append(obj);
        saveUserData();
        stream << "Registration successful\n";
    } else if (command == "LOGIN") {
        if (parts.size() != 3) {
            stream << "Invalid parameters\n";
            return;
        }
        QString username = parts[1];
        QString password = parts[2];

        bool valid = false;
        for (auto it = users.begin();it!=users.end();it++) {
            QJsonObject obj = (*it).toObject();
            if (obj["username"].toString() == username &&
                obj["password"].toString() == hashPassword(password)) {
                valid = true;
                break;
            }
        }

        if (valid) {
            stream << "Login successful\n";
        } else {
            stream << "Invalid username or password\n";
        }
    } else if (command == "RESET_PASSWORD") {
        if (parts.size() != 3) {
            stream << "Invalid parameters\n";
            return;
        }
        QString phone = parts[1];
        QString newPassword = parts[2];

        bool valid = false;
        for(auto it = users.begin();it!=users.end();it++){
            QJsonObject obj = (*it).toObject();
            if (obj["phone"].toString() == phone) {
                obj["password"] = hashPassword(newPassword);
                *it = obj;
                valid = true;
                break;
            }
        }

        if (valid) {
            saveUserData();
            stream << "Password reset successful\n";
        } else {
            stream << "Invalid phone number\n";
        }
    } else {
        stream << "Unknown command\n";
    }

    socket->flush();
}
