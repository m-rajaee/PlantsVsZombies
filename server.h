#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);


protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QSet<QTcpSocket*> clients;
    QJsonArray users; // array to hold user information
    QJsonArray History;
    void loadUserData();
    void saveUserData();
    void loadHistory();
    void saveHistory();
    void processRequest(QTcpSocket *socket, const QString &request);
    QString hashPassword(const QString &password); // function to hash passwords
};

#endif // SERVER_H
