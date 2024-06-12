#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QStandardPaths>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void Get_Entered_Information(QString Name,QString Username,QString PhoneNumber,QString Email,QString Password);
    void on_pushButton_clicked();
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);
    void displayMessage(const QString& str);
    void on_pushButton_sendMessage_clicked();
    void on_pushButton_sendAttachment_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket* socket;
};
#endif // MAINWINDOW_H
