#include "start.h"
#include "ui_start.h"
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QMessageBox>
Start::Start(Client* c,QWidget *parent)
    : QDialog(parent),
    ui(new Ui::Start)
{
    player = c;
    ui->setupUi(this);
    this->resize(1510, 800);
    QGridLayout *MainLayout = new QGridLayout(this);
    QLabel *BackgroundLabel = new QLabel(this);
    QPixmap BackGround(":/bg/bg/B2vQNpC.png");
    BackGround = BackGround.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    BackgroundLabel->setPixmap(BackGround);
    BackgroundLabel->setFixedSize(this->size());
    ip = new QLineEdit(); port = new QLineEdit();
    BackgroundLabel->lower();
    startButton = new QPushButton("Start The Game", this);
    startButton->setStyleSheet(
        "QPushButton {"
        "background-color: #90ee90;"
        "border: 2px solid #4CAF50;"
        "border-radius: 10px;"
        "color: black;"
        "padding: 10px 20px;"
        "font-size: 16px;"
        "font-weight: bold;"
        "text-align: center;"
        "box-shadow: 3px 3px 5px #999999;"
        "}"
        "QPushButton:pressed {"
        "background-color: #45a049;"
        "box-shadow: inset 3px 3px 5px #666666;"
        "}"
        );
    QFont LabelFont("Comic Sans MS", 14, QFont::Bold);
    QLabel *InstructionLabel = new QLabel("Enter Server IP and Port:", this);
    InstructionLabel->setFont(LabelFont); InstructionLabel->setStyleSheet("QLabel { color : white; }");
    QVBoxLayout *InputLayout = new QVBoxLayout();
    InputLayout->addWidget(InstructionLabel,0,Qt::AlignBottom);
    InputLayout->addWidget(ip);
    InputLayout->addWidget(port);
    QVBoxLayout *CenterLayout = new QVBoxLayout();
    CenterLayout->addLayout(InputLayout);
    CenterLayout->addWidget(startButton, 0, Qt::AlignCenter);
    QFont buttonFont(LabelFont);
    startButton->setFont(buttonFont);
    MainLayout->addLayout(CenterLayout,0,Qt::AlignLeft);
    MainLayout->addWidget(BackgroundLabel, 0, 0, 3, 3);
    MainLayout->addWidget(startButton, 1, 1, Qt::AlignCenter);
    MainLayout->setRowStretch(0, 20);
    MainLayout->setRowStretch(2, 1);
    MainLayout->setColumnStretch(0, 1);
    MainLayout->setColumnStretch(2, 1);
    setLayout(MainLayout);
    connect(startButton,SIGNAL(clicked(bool)),this,SLOT(goToAuthorization()));
}

Start::~Start()
{
    delete ui;
}

void Start::goToAuthorization()
{
    bool ConnectionSuccessful = player->connectToServer(ip->text(),port->text().toInt());
    if(ConnectionSuccessful){
            Authorization* page = new Authorization(player);
            page->show();
            this->close();
    }else
         QMessageBox::critical(nullptr, "Connection Error", "Can't Connect To server\nCheck Ip & Port Validation And Try Again");
}

