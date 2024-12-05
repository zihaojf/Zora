#include "zora.h"
#include "./ui_zora.h"

Zora::Zora(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Zora)
{
    ui->setupUi(this);
    this->resize(QSize(800,800));

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

    initbutton();//初始化按钮
    initpsystemtray();//初始化系统托盘

}

Zora::~Zora()
{
    delete ui;
    delete timer;
    delete bodyImage;
    delete closebtn;
    delete musicbtn;
    delete accountbtn;
    delete lifebtn;
    delete passwordbtn;
    delete classbtn;
    delete workbtn;
    delete minbtn;

    delete account_window;
    delete music_window;
    delete password_window;
    delete life_window;
    delete work_window;
    delete class_window;
    delete psystemtray;

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
        bodyImage->move(this->frameGeometry().width()/2,this->frameGeometry().height()/2);
        bodyImage->setPixmap(standMap[flag].scaled(body_size,body_size));
    flag++;
    if(flag>32) flag = 0;
}

void Zora::jumpMovement(){//跳跃
    static int flag = 0;

    bodyImage->resize(body_size*2,body_size*2);
    if(flag<=54)
        bodyImage->move(this->frameGeometry().width()/2,this->frameGeometry().height()/2);
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
        bodyImage->move(this->frameGeometry().width()/2,this->frameGeometry().height()/2);
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
        bodyImage->move(this->frameGeometry().width()/2,this->frameGeometry().height()/2);
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
    else if(event->button() == Qt::RightButton){
        if(buttonswitch==0){
            buttonswitch=1;
            setbutton_invisiable();
        }
        else{
            buttonswitch=0;
            setbutton_invisiable();
        }

    }
}

//初始化按钮
void Zora::initbutton(){
    closebtn = new QPushButton(this);
    musicbtn = new QPushButton(this);
    accountbtn = new QPushButton(this);
    classbtn = new QPushButton(this);
    workbtn = new QPushButton(this);
    passwordbtn = new QPushButton(this);
    lifebtn = new QPushButton(this);
    minbtn = new QPushButton(this);

    closebtn->setIcon(QIcon(":/image/mainbutton_icon/close.png"));
    musicbtn->setIcon(QIcon(":/image/mainbutton_icon/music.png"));
    accountbtn->setIcon(QIcon(":/image/mainbutton_icon/account.png"));
    classbtn->setIcon(QIcon(":/image/mainbutton_icon/class.png"));
    workbtn->setIcon(QIcon(":/image/mainbutton_icon/work.png"));
    passwordbtn->setIcon(QIcon(":/image/mainbutton_icon/password.png"));
    lifebtn->setIcon(QIcon(":/image/mainbutton_icon/life.png"));
    minbtn->setIcon(QIcon(":/image/mainbutton_icon/min.png"));

    setbutton_size();//设置按钮的大小
    buttonswitch = 0;//默认设置为不显示
    setbutton_invisiable();//设置显示与否
    //新建窗口指针
    music_window = new music(this);
    account_window = new account(this);
    class_window = new schoolclass(this);
    work_window = new work(this);
    password_window = new password(this);
    life_window = new life(this);

    music_window->hide();
    account_window->hide();
    class_window->hide();
    work_window->hide();
    password_window->hide();
    life_window->hide();

    //槽和信号，点击按钮打开对应的窗口
    connect(closebtn,&QPushButton::clicked,this,&Zora::closebtn_push);
    connect(musicbtn,&QPushButton::clicked,this,&Zora::musicbtn_push);
    connect(accountbtn,&QPushButton::clicked,this,&Zora::accountbtn_push);
    connect(classbtn,&QPushButton::clicked,this,&Zora::classbtn_push);
    connect(workbtn,&QPushButton::clicked,this,&Zora::workbtn_push);
    connect(passwordbtn,&QPushButton::clicked,this,&Zora::passwordbtn_push);
    connect(lifebtn,&QPushButton::clicked,this,&Zora::lifebtn_push);
    connect(minbtn,&QPushButton::clicked,this,&Zora::minbtn_push);




}

void Zora::initpsystemtray(){
    psystemtray = new QSystemTrayIcon(this);
    psystemtray->setToolTip(tr("你好，我是Zora!"));
    psystemtray->setIcon(QIcon(":/image/icon/systemtray_icon.png"));
    psystemtray->show();
    connect(psystemtray,&QSystemTrayIcon::activated,this,&Zora::systemtray_push);
}

void Zora::setbutton_size(){
    button_size = body_size;
    int btnX =  this->frameGeometry().width()/2- button_size*3/5-10;
    int btnY = this->frameGeometry().height()/2 - button_size;
    int btnWidth = button_size/2;
    int btnHeight = button_size/2;

    closebtn->setGeometry(btnX,btnY,btnWidth,btnHeight);
    musicbtn->setGeometry(btnX,btnY+btnHeight,btnWidth,btnHeight);
    accountbtn->setGeometry(btnX,btnY+2*btnHeight,btnWidth,btnHeight);
    classbtn->setGeometry(btnX,btnY+3*btnHeight,btnWidth,btnHeight);
    workbtn->setGeometry(btnX,btnY+4*btnHeight,btnWidth,btnHeight);
    passwordbtn->setGeometry(btnX,btnY+5*btnHeight,btnWidth,btnHeight);
    lifebtn->setGeometry(btnX,btnY+6*btnHeight,btnWidth,btnHeight);
    minbtn->setGeometry(btnX,btnY+7*btnHeight,btnWidth,btnHeight);

}

void Zora::setbutton_invisiable(){//设置按钮是否可见
    closebtn->setVisible(buttonswitch);
    musicbtn->setVisible(buttonswitch);
    accountbtn->setVisible(buttonswitch);
    classbtn->setVisible(buttonswitch);
    workbtn->setVisible(buttonswitch);
    passwordbtn->setVisible(buttonswitch);
    lifebtn->setVisible(buttonswitch);
    minbtn->setVisible(buttonswitch);

    //移动窗口坐标↓


}


void Zora::closebtn_push(){//关闭按钮
    account_window->close();
    music_window->close();
    class_window->close();
    work_window->close();
    password_window->close();
    life_window->close();
    this->close();

    delete ui;
    delete timer;
    delete bodyImage;
    delete closebtn;
    delete musicbtn;
    delete accountbtn;
    delete lifebtn;
    delete passwordbtn;
    delete classbtn;
    delete workbtn;
    delete minbtn;

    delete account_window;
    delete music_window;
    delete password_window;
    delete life_window;
    delete work_window;
    delete class_window;
    delete psystemtray;
}

void Zora::musicbtn_push(){//音乐按钮
    if(music_window->isHidden()){//如果窗口隐藏
        music_window->move(600,400);
        music_window->setWindowFlags(Qt::Window);
        music_window->setWindowTitle("音乐播放");
        music_window->setFixedSize(1200,800);
        music_window->show();
        account_window->hide();
        class_window->hide();
        work_window->hide();
        password_window->hide();
        life_window->hide();

    }
    else
        music_window->hide();//窗口可见就关闭

    buttonswitch=0;
    setbutton_invisiable();

}

void Zora::accountbtn_push(){
    if(account_window->isHidden()){//如果窗口隐藏
        account_window->setWindowFlags(Qt::Window);  // 设置为顶级窗口
        account_window->setWindowTitle("记账"); // 设置窗口标题
        account_window->setFixedSize(800,600);//设置窗口固定大小
        account_window->move(800,600);//窗口移动

        account_window->show();
        music_window->hide();
        class_window->hide();
        work_window->hide();
        password_window->hide();
        life_window->hide();

    }
    else
        account_window->hide();//窗口可见就关闭

    buttonswitch=0;

}

void Zora::classbtn_push(){
    if(class_window->isHidden()){//如果窗口隐藏
        class_window->move(0,0);
        class_window->show();
        account_window->hide();
        music_window->hide();
        work_window->hide();
        password_window->hide();
        life_window->hide();

    }
    else
        class_window->hide();//窗口可见就关闭

    buttonswitch=0;
    setbutton_invisiable();

}

void Zora::workbtn_push(){
    if(work_window->isHidden()){//如果窗口隐藏
        work_window->move(0,0);
        work_window->show();
        account_window->hide();
        class_window->hide();
        music_window->hide();
        password_window->hide();
        life_window->hide();

    }
    else
        work_window->hide();//窗口可见就关闭

    buttonswitch=0;
    setbutton_invisiable();

}

void Zora::passwordbtn_push(){
    if(password_window->isHidden()){//如果窗口隐藏
        password_window->move(0,0);
        password_window->show();
        account_window->hide();
        class_window->hide();
        work_window->hide();
        music_window->hide();
        life_window->hide();

    }
    else
        password_window->hide();//窗口可见就关闭

    buttonswitch=0;
    setbutton_invisiable();

}

void Zora::lifebtn_push(){
    if(life_window->isHidden()){//如果窗口隐藏
        life_window->move(0,0);
        life_window->show();
        account_window->hide();
        class_window->hide();
        work_window->hide();
        password_window->hide();
        music_window->hide();

    }
    else
        life_window->hide();//窗口可见就关闭

    buttonswitch=0;
    setbutton_invisiable();

}

void Zora::minbtn_push(){
    this->hide();

    account_window->hide();
    class_window->hide();
    work_window->hide();
    password_window->hide();
    music_window->hide();
    life_window->hide();

}

void Zora::systemtray_push()
{
    if(this->isHidden())
        this->show();

}







