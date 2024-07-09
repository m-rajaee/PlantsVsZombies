#include "server.h"
#include <QTextStream>
#include <QDebug>
#include <QCryptographicHash>
Server::Server(QObject *parent) : QTcpServer(parent)
{
    loadUserData();
    loadHistory();
    if (this->listen(QHostAddress::Any, 12345)) {
        qDebug() << "Server started!";
    } else {
        qDebug() << "Server could not start!";
    }
}

void Server::broadcastMessage(const QString &message)
{
    for(auto client : clients){
            QTextStream clientsream(client);
            clientsream << message;
            client->flush();
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    if (socket->setSocketDescriptor(socketDescriptor)) {
        connect(socket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &Server::onDisconnected);
        clients.insert(socket);
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
    QFile file("D:/Qt/temp3OfProject/users.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        users = doc.object().value("users").toArray();
        file.close();
    }
}
void Server::loadHistory(){
    QFile file("D:/Qt/temp3OfProject/history.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        History = doc.object().value("History").toArray();
        file.close();
    }
}

void Server::saveUserData()
{
    QFile file("D:/Qt/temp3OfProject/users.json");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject obj;
        obj["users"] = users;
        QJsonDocument doc(obj);
        file.write(doc.toJson());
        file.close();
    }
}
void Server:: saveHistory(){
    QFile file("D:/Qt/temp3OfProject/history.json");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject obj;
        obj["History"] = History;
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
    QStringList parts = request.split("|");
    if (parts.isEmpty()) {
        stream << "Invalid request";
        return;
    }

    QString command = parts[0].toUpper();
    if (command == "REGISTER") {
        if (parts.size() != 6) {
            stream << "Invalid parameters";
            return;
        }
        QString username = parts[1];
        QString password = parts[2];
        QString name = parts[3];
        QString phone = parts[4];
        QString email = parts[5];
        qDebug() << username;
        bool exist = false;
        for (auto it = users.begin();it!=users.end();it++) {
            QJsonObject obj = (*it).toObject();
            if (obj["username"].toString() == username) {
                exist = true;
                break;
            }
        }
        if(exist){
            stream << "SingupErrorOfusername";
            return;
        }
        exist = false;
        for (auto it = users.begin();it!=users.end();it++) {
            QJsonObject obj = (*it).toObject();
            if (obj["phone"].toString() == phone) {
                exist = true;
                break;
            }
        }
        if(exist){
            stream << "SingupErrorOfPhoneNumeber";
            return;
        }
        QJsonObject obj;
        obj["username"] = username;
        obj["password"] = hashPassword(password);
        obj["name"] = name;
        obj["phone"] = phone;
        obj["email"] = email;
        users.append(obj);
        saveUserData();
        stream << "SignedUP";
    } else if (command == "LOGIN") {
        if (parts.size() != 3) {
            stream << "Invalid parameters";
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
            stream << "Loggedin"<< "|" << username;
        } else {
            stream << "LoginError";
        }
    } else if (command == "RESET_PASSWORD") {
        if (parts.size() != 3) {
            stream << "Invalid parameters";
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
            stream << "PasswordReseted";
        } else {
            stream << "PasswordResetError";
        }
    }else if (command == "ADD_HISTORY"){
        QString username = parts[1];
        QString opponent = parts[2];
        QString time = parts[3];
        QString role1 = parts[4];
        QString winner1 = parts[5];
        QString role2 = parts[6];
        QString winner2 = parts[7];
        QString winner = parts[8];
        bool exist = false;
        for (auto it = users.begin();it!=users.end();it++) {
            QJsonObject obj = (*it).toObject();
            if (obj["username"].toString() == username) {
                exist = true;
                break;
            }
        }
        if(!exist){
            qDebug() << "Username of player Doesn't Exist to Have Histoy";
            return;
        }
        exist = false;
        for (auto it = users.begin();it!=users.end();it++) {
            QJsonObject obj = (*it).toObject();
            if (obj["username"].toString() == opponent) {
                exist = true;
                break;
            }
        }
        if(!exist){
            qDebug() << "Username of opponent Does'nt Exist to Have Histoy";
            return;
        }
        QJsonObject obj;
        obj["username"] = username;
        obj["opponent"] = opponent;
        obj["time"] = time;
        obj["role1"] = role1;
        obj["winner1"] = winner1;
        obj["role2"] = role2;
        obj["winner2"] = winner2;
        obj["winner"] = winner;
        History.append(obj);
        saveHistory();
        stream << "New Game Added To History";
    }else if (command == "CHANGE_INFORMATION"){
        QString username = parts[1];
        QString newusername = parts[2];
        QString newpassword = parts[3];
        QString newname = parts[4];
        QString newphone = parts[5];
        QString newemail = parts[6];
        bool exist = false;
        for(auto it = users.begin();it!=users.end();it++){
            QJsonObject obj = (*it).toObject();
            if (obj["username"].toString() == newusername) {
                exist = true;
            }
        }
        if (exist) {
            stream << "ChangeInformationError";
            return;
        }
        for(auto it = users.begin();it!=users.end();it++){
            QJsonObject obj = (*it).toObject();
            if (obj["username"].toString() == username) {
                obj["username"] = newusername;
                obj["password"] = hashPassword(newpassword);
                obj["name"] = newname;
                obj["phone"] = newphone;
                obj["email"] = newemail;
                *it = obj;
                break;
            }
        }
        saveUserData();
        for(auto it = History.begin();it!=History.end();it++){
            QJsonObject obj = (*it).toObject();
            if (obj["username"].toString() == username) {
                obj["username"] = newusername;
                *it = obj;
            }
            if(obj["opponent"].toString() == username){
                obj["opponent"] = newusername;
                *it = obj;
            }
        }
        saveHistory();
        stream << "InformationChanged" << "|" << newusername;
    }else if(command == "SHOW_HISTORY"){
        QString username = parts[1];
        QFile file("D:/Qt/temp3OfProject/history.json");
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        QJsonObject jsonObject = doc.object();
        QJsonArray usersArray = jsonObject["History"].toArray();
        QString history;
        for (const QJsonValue &value : usersArray) {
            QJsonObject userObj = value.toObject();
            if (userObj["username"].toString() == username) {
                history.append("Opponent: " + userObj["opponent"].toString() + "\n");
                history.append("Time: " + userObj["time"].toString() + "\n");
                history.append("Role in Round One: " + userObj["role1"].toString() + "\n");
                history.append("Winner Of Round One: " + userObj["winner1"].toString() + "\n");
                history.append("Role in Round Two: " + userObj["role2"].toString() + "\n");
                history.append("Winner Of Round Two: " + userObj["winner2"].toString() + "\n");
                history.append("The Winner Of The Match : " + userObj["winner"].toString() + "\n");
                history.append("----------------------------------------------------\n");
            }
        }
        stream << "ShowHistory|"<<history;
    }else if(request == "MatchStarted"){
        QTcpSocket* player1 = *(clients.begin());
        QTcpSocket* player2 = *(++(clients.begin()));
        srand(time(NULL)); int side = rand() % 1;
        QTextStream player1Message(player1);
        QTextStream player2Message(player2);
        if(side == 0){
            player1Message << "StartTheMatch|Plant";
            player2Message << "StartTheMatch|Zombie";
        }else if(side ==1){
            player1Message << "StartTheMatch|Zombie";
            player2Message << "StartTheMatch|Plant";
        }
        player1->flush(); player2->flush(); return;
    }else if(parts[0] == "Round1Finished"){
        broadcastMessage(request);
    }else if(parts[0] == "Round2Finished"){
        broadcastMessage(request);
    }
    else {
        //Sending Request(Message) To other clients
        for(auto clientsocket : clients){
            if(clientsocket != socket){
                QTextStream clientsream(clientsocket);
                clientsream << request;
                clientsocket->flush();
            }
        }
    }
    socket->flush();
}
