#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QString>
class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject *parent = nullptr);
    bool connectToServer(const QString &host, quint16 port);
    void registerUser(const QString &username, const QString &password, const QString &name, const QString &phone, const QString &email);
    void loginUser(const QString &username, const QString &password);
    void resetPassword(const QString &phone, const QString &newPassword);
    void addHistory(const QString& username,const QString& opponent,const QString& role1,const QString& winner1,const QString& role2,const QString& winner2,const QString& winner);
    void changeInformation(const QString &username, const QString& newusername ,const QString &newpassword, const QString &newname, const QString &newphone, const QString & newemail);
    void showHistory(const QString& username);
    void sendMessage(const QString& message);
    bool isConnectedToServer();
    QString username;
    struct matchdata{
        QString oponnent;
        QString roleInRound1;
        QString winnerOfRound1;
        QString roleInRound2;
        QString winnerOfRound2;
        QString winnerOfTheMatch;
    };
    matchdata data;
    int numberOfWins;
    int currentRoundNumber;
private slots:
    void onReadyRead();
    void getOrder(QString order);
signals:
    void Order(QString);
    void matchFinished();
private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
