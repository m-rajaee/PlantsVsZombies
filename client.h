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

private slots:
    void onReadyRead();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
