#include "zora.h"
#include "./ui_zora.h"

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

    currentAnimation = AnimationState::stand;//设置默认状态为stand
    timer = new QTimer;
    timer->start(40);
    connect(timer,&QTimer::timeout,this,&Zora::timeoutHandler);

    ImageLoad();
    bodyImage = new QLabel(this);//主题图片指针初始化



}

Zora::~Zora()
{
    delete ui;
}

void Zora:: ImageLoad(){//主题图片导入
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

void Zora::timeoutHandler(){//控制timer的链接对象
    if(currentAnimation == AnimationState::stand){
        standMovement();
    }
    else if(currentAnimation == AnimationState::jump){
        jumpMovement();
    }
    else if(currentAnimation == AnimationState::tumble){
        tumbleMovement();
    }
    else lieMovement();

}


void Zora::standMovement(){//站立
    static int flag = 0;
    bodyImage->resize(body_size,body_size);
    if(flag<=32)
        bodyImage->setPixmap(standMap[flag].scaled(body_size,body_size));
    flag++;
    if(flag>32) flag = 0;
}

void Zora::jumpMovement(){//跳跃
    static int flag = 0;

    bodyImage->resize(body_size*2,body_size*2);
    if(flag<=54)
        bodyImage->setPixmap(jumpMap[flag].scaled(body_size*2,body_size*2));
    flag++;
    if(flag>54){
        flag = 0;
        currentAnimation = AnimationState::stand;
        standMovement();
    }
}

void Zora::tumbleMovement(){//空滚翻
    static int flag = 0;

    bodyImage->resize(body_size*2,body_size*2);

    if(flag<=55)
        bodyImage->setPixmap(tumbleMap[flag].scaled(body_size*2,body_size*2));
    flag++;
    if(flag>55){
        flag = 0;
        currentAnimation = AnimationState::stand;
        standMovement();
    }
}

void Zora::lieMovement(){//趴下
    static int flag = 0;

    bodyImage->resize(body_size*2,body_size*2);
    if(flag<=55)
        bodyImage->setPixmap(lieMap[flag].scaled(body_size*2,body_size*2));
    flag++;
    if(flag>55){
        flag = 0;
        currentAnimation = AnimationState::stand;
        standMovement();
    }
}

void Zora::mouseMoveEvent(QMouseEvent *event){//长按移动
    if(event->buttons() & Qt::LeftButton){//只要按下了左键，按位与
        this->move(event->globalPos() - MoveTopLeft);
    }
}


void Zora::mousePressEvent(QMouseEvent *event){//单击切换状态
    if(event->button() == Qt::LeftButton){//只按下左键
        MoveTopLeft = event->pos();
        int RandomFlag = QRandomGenerator::global()->bounded(3);
        if(RandomFlag==0){
            currentAnimation = AnimationState::jump;
            jumpMovement();
        }
        else if(RandomFlag == 1){
            currentAnimation = AnimationState::tumble;
            tumbleMovement();
        }
        else {
            currentAnimation = AnimationState::lie;
            lieMovement();
        }
    }
}




