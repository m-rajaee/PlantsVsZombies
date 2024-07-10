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
    QGridLayout *main_layout = new QGridLayout(this);
    QLabel *background_label = new QLabel(this);
    QPixmap bkgnd(":/bg/bg/B2vQNpC.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    background_label->setPixmap(bkgnd);
    background_label->setFixedSize(this->size());
    ip = new QLineEdit(); port = new QLineEdit();
    background_label->lower();
    start_button = new QPushButton("Start The Game", this);
    start_button->setStyleSheet(
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
    QFont labelFont("Comic Sans MS", 14, QFont::Bold);
    QLabel *instruction_label = new QLabel("Enter Server IP and Port:", this);
    instruction_label->setFont(labelFont); instruction_label->setStyleSheet("QLabel { color : white; }");
    QVBoxLayout *input_layout = new QVBoxLayout();
    input_layout->addWidget(instruction_label,0,Qt::AlignBottom);
    input_layout->addWidget(ip);
    input_layout->addWidget(port);
    QVBoxLayout *center_layout = new QVBoxLayout();
    center_layout->addLayout(input_layout);
    center_layout->addWidget(start_button, 0, Qt::AlignCenter);
    QFont buttonFont("Comic Sans MS", 14, QFont::Bold);
    start_button->setFont(buttonFont);
    main_layout->addLayout(center_layout,0,Qt::AlignLeft);
    main_layout->addWidget(background_label, 0, 0, 3, 3);
    main_layout->addWidget(start_button, 1, 1, Qt::AlignCenter);
    main_layout->setRowStretch(0, 20);
    main_layout->setRowStretch(2, 1);
    main_layout->setColumnStretch(0, 1);
    main_layout->setColumnStretch(2, 1);
    setLayout(main_layout);
    connect(start_button,SIGNAL(clicked(bool)),this,SLOT(gotologin()));
}

Start::~Start()
{
    delete ui;
}

void Start::gotologin()
{
    if(player->connectToServer(ip->text(),port->text().toInt())){
            Authorization* page = new Authorization(player);
            page->show();
            this->close();
    }else
         QMessageBox::critical(nullptr, "Connection Error", "Can't Connect To server\nCheck Ip & Port Validation And Try Again");
}

