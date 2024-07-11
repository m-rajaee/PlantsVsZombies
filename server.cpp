#include "server.h"
#include <QTextStream>
#include <QDebug>
#include <QCryptographicHash>
Server::Server(QObject *parent) : QTcpServer(parent)
{
    loadUsersDataFromFile();
    loadHistoryFromFile();
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
        connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
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

void Server::loadUsersDataFromFile()
{
    QFile file("D:/Qt/temp3OfProject/users.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        users = doc.object().value("users").toArray();
        file.close();
        qDebug() << "Loaded";
    }
}
void Server::loadHistoryFromFile(){
    QFile file("D:/Qt/temp3OfProject/history.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        history = doc.object().value("History").toArray();
        file.close();
    }
}

void Server::saveUsersDataToFile()
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
void Server:: saveHistoryToFile(){
    QFile file("D:/Qt/temp3OfProject/history.json");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject obj;
        obj["History"] = history;
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
    QStringList orderParts = request.split("|");
    if (orderParts.isEmpty()) {
        stream << "Invalid request";
        return;
    }

    QString command = orderParts[0].toUpper();
    if (command == "REGISTER") {
        if (orderParts.size() != 6) {
            stream << "Invalid parameters";
            return;
        }
        QString username = orderParts[1];
        QString password = orderParts[2];
        QString name = orderParts[3];
        QString phone = orderParts[4];
        QString email = orderParts[5];
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
        saveUsersDataToFile();
        stream << "SignedUP";
    } else if (command == "LOGIN") {
        if (orderParts.size() != 3) {
            stream << "Invalid parameters";
            return;
        }
        QString username = orderParts[1];
        QString password = orderParts[2];

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
        if (orderParts.size() != 3) {
            stream << "Invalid parameters";
            return;
        }
        QString phone = orderParts[1];
        QString newPassword = orderParts[2];

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
            saveUsersDataToFile();
            stream << "PasswordReseted";
        } else {
            stream << "PasswordResetError";
        }
    }else if (command == "ADD_HISTORY"){
        QString username = orderParts[1];
        QString opponent = orderParts[2];
        QString time = orderParts[3];
        QString role1 = orderParts[4];
        QString winner1 = orderParts[5];
        QString role2 = orderParts[6];
        QString winner2 = orderParts[7];
        QString winner = orderParts[8];
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
        history.append(obj);
        saveHistoryToFile();
        stream << "New Game Added To History";
    }else if (command == "CHANGE_INFORMATION"){
        QString username = orderParts[1];
        QString newusername = orderParts[2];
        QString newpassword = orderParts[3];
        QString newname = orderParts[4];
        QString newphone = orderParts[5];
        QString newemail = orderParts[6];
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
        saveUsersDataToFile();
        for(auto it = history.begin();it!=history.end();it++){
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
        saveHistoryToFile();
        stream << "InformationChanged" << "|" << newusername;
    }else if(command == "SHOW_HISTORY"){
        QString username = orderParts[1];
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
    }else if(orderParts[0] == "Round1Finished"){
        broadcastMessage(request);
    }else if(orderParts[0] == "Round2Finished"){
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
