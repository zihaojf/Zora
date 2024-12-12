#include "work.h"
#include "ui_work.h"

work::work(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::work)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);//去掉窗口的标题栏
    setStyleSheet("background: rgba(255, 255, 255, 93%);");
    init();

}

work::~work()
{
    delete ui;
}

void work::mouseMoveEvent(QMouseEvent *event){//长按移动
    if(event->buttons() & Qt::LeftButton){//只要按下了左键，按位与
        this->move(event->globalPos() - MoveTopLeft);
    }
}


void work::init(){
    worktime = 1500;
    relaxtime = 300;
    workrelaxcondition = 0;//工作状态

    setting_window = new worksetting(this);
    setting_window->setWindowFlags(Qt::Window);  // 设置为顶级窗口
    setting_window->setWindowTitle("番茄钟设置"); // 设置窗口标题
    setting_window->setFixedSize(400,250);//设置窗口固定大小
    setting_window->move(800,500);//窗口移动

    settingbtn = new QPushButton(this);
    startbtn = new QPushButton(this);
    removebtn = new QPushButton(this);
    pausebtn = new QPushButton(this);

    settingbtn->setGeometry(20,40,50,50);
    startbtn->setGeometry(20,130,50,50);
    pausebtn->setGeometry(20,130,50,50);
    removebtn->setGeometry(20,220,50,50);
    settingbtn->setIconSize(QSize(40,40));
    startbtn->setIconSize(QSize(40,40));
    pausebtn->setIconSize(QSize(40,40));
    removebtn->setIconSize(QSize(40,40));
    pausebtn->hide();

    settingbtn->setIcon(QIcon(":/image/work/settings.svg"));
    startbtn->setIcon(QIcon(":/image/work/start.svg"));
    removebtn->setIcon(QIcon(":/image/work/remove.svg"));
    pausebtn->setIcon(QIcon(":/image/work/pause.svg"));

    settingbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                              "QPushButton:hover { background-color: #f0f0f0; }");
    startbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                            "QPushButton:hover { background-color: #f0f0f0; }");
    removebtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                             "QPushButton:hover { background-color: #f0f0f0; }");
    pausebtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                            "QPushButton:hover { background-color: #f0f0f0; }");

    connect(startbtn,&QPushButton::clicked,this,&work::startbtn_push);
    connect(pausebtn,&QPushButton::clicked,this,&work::pausebtn_push);
    connect(removebtn,&QPushButton::clicked,this,&work::removebtn_push);
    connect(settingbtn,&QPushButton::clicked,this,&work::settingbtn_push);

    connect(setting_window,&worksetting::sendata,this,&work::receivedata);

    timelabel = new QLabel(this);
    timelabel->setAlignment(Qt::AlignCenter);
    timelabel->move(70,80);
    timelabel->setFixedSize(QSize(400,100));
    timelabel->setStyleSheet("color:#E84A4A;background: transparent;");
    QFont font("Arial", 55, QFont::Bold); // 选择字体、大小和粗细
    timelabel->setFont(font);

    statelabel = new QLabel(this);
    statelabel->setAlignment(Qt::AlignCenter);
    statelabel->move(170,220);
    statelabel->setStyleSheet("color:#E8B49C;background: transparent;");
    QFont font1("微软雅黑", 15, QFont::Bold); // 选择字体、大小和粗细
    statelabel->setFont(font1);

    int m = worktime/60;
    int s = worktime%60;
    statelabel->setText(QString("番茄时钟READY"));
    timelabel->setText(QString("%1:%2").arg(m, 2, 10, QLatin1Char('0')).arg(s, 2, 10, QLatin1Char('0')));

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&work::updatetime);


}

void work::updatetime(){
    if(workrelaxcondition){//休息状态
        if(relaxtime==0){
            timer->stop();
            timelabel->setText("时间到！");
            workrelaxcondition = 0;
        }
        else{
            int m = relaxtime/60;
            int s = relaxtime%60;
            statelabel->setText(QString("休息中"));
            timelabel->setText(QString("%1:%2").arg(m, 2, 10, QLatin1Char('0')).arg(s, 2, 10, QLatin1Char('0')));
        }
        relaxtime--;
    }
    else{//工作状态
        if(worktime==0){
            workrelaxcondition = 1;//调整为休息状态
        }
        else{
            int m = worktime/60;
            int s = worktime%60;
            statelabel->setText(QString("工作中"));
            timelabel->setText(QString("%1:%2").arg(m, 2, 10, QLatin1Char('0')).arg(s, 2, 10, QLatin1Char('0')));
        }
        worktime--;
    }

}

void work::startbtn_push(){
    statelabel->setText(QString("工作中"));
    timer->start(1000);
    pausebtn->show();
    startbtn->hide();
}

void work::removebtn_push(){
    timer->stop();
    worktime = worktimeconst;
    relaxtime = relaxtimeconst;
    workrelaxcondition = 0;
    int m = worktime/60;
    int s = worktime%60;
    statelabel->setText(QString("番茄时钟READY"));
    timelabel->setText(QString("%1:%2").arg(m, 2, 10, QLatin1Char('0')).arg(s, 2, 10, QLatin1Char('0')));
    pausebtn->hide();
    startbtn->show();
}

void work::pausebtn_push(){
    timer->stop();
    statelabel->setText(QString("暂停中"));
    pausebtn->hide();
    startbtn->show();
}

void work::settingbtn_push(){
    setting_window->show();
    pausebtn_push();
}

void work::receivedata(int setworktime,int setrelaxtime){
    qDebug()<<setworktime<<setrelaxtime;
    worktimeconst = setworktime;
    relaxtimeconst = setrelaxtime;
    worktime = setworktime;
    relaxtime = setrelaxtime;
    int m = worktime/60;
    int s = worktime%60;
    statelabel->setText(QString("番茄时钟READY"));
    timelabel->setText(QString("%1:%2").arg(m, 2, 10, QLatin1Char('0')).arg(s, 2, 10, QLatin1Char('0')));
    timer->stop();
}

void work::setstylesheet(){


}
