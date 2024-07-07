#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QString>
class Client : public QObject
{
    Q_OBJECT

public:
    Client(QObject *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);
    void registerUser(const QString &username, const QString &password, const QString &name, const QString &phone, const QString &email);
    void loginUser(const QString &username, const QString &password);
    void resetPassword(const QString &phone, const QString &newPassword);
    void addHistory(const QString& username,const QString& opponent,const QString& role1,const QString& winner1,const QString& role2,const QString& winner2,const QString& role3 ,const QString& winner3,const QString& winner);
    void ChangeInformation(const QString &username, const QString& newusername ,const QString &newpassword, const QString &newname, const QString &newphone, const QString & newemail);
    void ShowHistory(const QString& username);
    void SendMessage(const QString& message);
    QString Username;
private slots:
    void onReadyRead();
    void getOrder(QString order);
signals:
    void Order(QString);
private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
