#include "zora.h"
#include "./ui_zora.h"
#include <complex>

Zora::Zora(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Zora)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);//去掉窗口的标题栏
    setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    Qt::WindowFlags m_flag = windowFlags();
    setWindowFlags(m_flag|Qt::WindowStaysOnTopHint);//设置窗口置顶

    int coord_x,coord_y;

    body_size = 130;
    coord_x = 1500;
    coord_y = 700;

    move(coord_x,coord_y);

    timer = new QTimer;
    timer->start(40);
    connect(timer,&QTimer::timeout,this,&Zora::standMovement);

    ImageLoad();
    standImage = new QLabel(this);
    jumpImage = new QLabel(this);
    tumbleImage = new QLabel(this);
    lieImage = new QLabel(this);


}

Zora::~Zora()
{
    delete ui;
}

void Zora:: ImageLoad(){
    for(int i = 1;i<=33;i++){
        standMap.push_back(QPixmap(QString(":/image/movement/stand/%1.png").arg(i)));
    }

    for(int i = 1;i<=55;i++){
        jumpMap.push_back(QPixmap(QString(":/image/movement/jump/%1.png").arg(i)));
    }

    for(int i = 1;i<=56;i++){
        tumbleMap.push_back(QPixmap(QString(":/image/movement/tumble/%1.png").arg(i)));
    }

    for(int i = 1;i<=56;i++){
        lieMap.push_back(QPixmap(QString(":/image/movement/lie/%1.png").arg(i)));
    }



}

void Zora::standMovement(){
    static int flag = 0;
    standImage->resize(body_size,body_size);
    if(flag<=32)
        standImage->setPixmap(standMap[flag].scaled(body_size,body_size));
    flag++;
    if(flag>32) flag = 0;
}
