#include "life.h"
#include "ui_life.h"

life::life(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::life)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);//去掉窗口的标题栏
    initpage();
    initnotepage();
    initlistpage();
    creat_notedatabase_connection();
}

life::~life()
{
    delete ui;
}

void life::initpage(){
    notepage = new QWidget(this);
    listpage = new QWidget(this);
    settingpage = new QWidget(this);
    notedetailpage = new QWidget(this);
    listdetailpage = new QWidget(this);
    noteaddpage = new QWidget(this);
    listaddpage = new QWidget(this);
    stackedwidget = new QStackedWidget(this);

    stackedwidget->addWidget(notepage);//堆叠添加日记页面
    stackedwidget->addWidget(listpage);//堆叠添加待办页面
    stackedwidget->addWidget(settingpage);//堆叠添加设置页面
    stackedwidget->addWidget(notedetailpage);//堆叠添加日记详情页面
    stackedwidget->addWidget(listdetailpage);//堆叠添加待办详情页面
    stackedwidget->addWidget(noteaddpage);//堆叠日记添加页面
    stackedwidget->addWidget(listaddpage);//堆叠待办添加页面
    stackedwidget->setCurrentIndex(0);//设置当前页面索引
    stackedwidget->setGeometry(50, 30, 1150, 760);
    notebtn = new QPushButton(this);
    listbtn = new QPushButton(this);
    settingbtn = new QPushButton(this);
    closebtn = new QPushButton(this);
    noteaddbtn = new QPushButton(notepage);
    listaddbtn = new QPushButton(listpage);
    //左侧侧边栏按钮设置
    settingbtn->move(0,750);
    notebtn->move(7,50);
    listbtn->move(0,100);
    settingbtn->setIconSize(QSize(40,40));
    notebtn->setIconSize(QSize(35,35));
    listbtn->setIconSize(QSize(50,50));
    closebtn->setIconSize(QSize(30,30));

    //关闭按钮
    closebtn->move(1150,0);
    closebtn->setIconSize(QSize(40,40));

    //添加按钮
    noteaddbtn->move(1000,650);
    noteaddbtn->setIconSize(QSize(80,80));
    listaddbtn->move(1000,650);
    listaddbtn->setIconSize(QSize(80,80));

    notebtn->setIcon(QIcon(":/image/lifeandlist/notebtn_yellow.svg"));
    listbtn->setIcon(QIcon(":/image/lifeandlist/listbtn.svg"));
    settingbtn->setIcon(QIcon(":/image/lifeandlist/settingbtn.svg"));
    closebtn->setIcon(QIcon(":/image/lifeandlist/closebtn.svg"));
    noteaddbtn->setIcon(QIcon(":/image/lifeandlist/addbtn.svg"));
    listaddbtn->setIcon(QIcon(":/image/lifeandlist/addbtn.svg"));

    //按钮样式
    settingbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                              "QPushButton:hover { background-color: #f0f0f0; }");
    closebtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                            "QPushButton:hover { background-color: #f0f0f0; }");
    notebtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                             "QPushButton:hover { background-color: #f0f0f0; }");
    listbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                            "QPushButton:hover { background-color: #f0f0f0; }");
    noteaddbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                           "QPushButton:hover { background-color: #f0f0f0; }");
    listaddbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                           "QPushButton:hover { background-color: #f0f0f0; }");

    connect(closebtn,&QPushButton::clicked,this,&life::closebtn_push);
    connect(notebtn,&QPushButton::clicked,this,&life::notebtn_push);
    connect(listbtn,&QPushButton::clicked,this,&life::listbtn_push);
    connect(settingbtn,&QPushButton::clicked,this,&life::settingbtn_push);
    connect(noteaddbtn,&QPushButton::clicked,this,&life::noteaddbtn_push);
    connect(listaddbtn,&QPushButton::clicked,this,&life::listaddbtn_push);

    //页面左上角状态初始化
    QLabel *notestatelabel = new QLabel(notepage);
    notestatelabel->setText("笔记");
    notestatelabel->setStyleSheet("color:#F6B128");
    QFont font("微软雅黑",30,QFont::Bold);
    notestatelabel->setFont(font);
    notestatelabel->move(30,0);
    QLabel *liststatelabel = new QLabel(listpage);
    liststatelabel->setText("待办");
    liststatelabel->setStyleSheet("color:#F6B128");
    liststatelabel->setFont(font);
    liststatelabel->move(30,0);
    QLabel *settingstatelabel = new QLabel(settingpage);
    settingstatelabel->setText("设置");
    settingstatelabel->setStyleSheet("color:#F6B128");
    settingstatelabel->move(30,0);
    settingstatelabel->setFont(font);

}

void life::initnotepage(){


}

void life::initlistpage(){

}

void life::initsettingpage(){

}




void life::mouseMoveEvent(QMouseEvent *event){//长按移动
    if(event->buttons() & Qt::LeftButton){//只要按下了左键，按位与
        this->move(event->globalPos() - topleft);
    }
}

void life::closebtn_push(){
    this->close();
}

void life::notebtn_push(){
    stackedwidget->setCurrentIndex(0);
    notebtn->setIcon(QIcon(":/image/lifeandlist/notebtn_yellow.svg"));
    listbtn->setIcon(QIcon(":/image/lifeandlist/listbtn.svg"));
    settingbtn->setIcon(QIcon(":/image/lifeandlist/settingbtn.svg"));
}

void life::listbtn_push(){
    stackedwidget->setCurrentIndex(1);
    notebtn->setIcon(QIcon(":/image/lifeandlist/notebtn.svg"));
    listbtn->setIcon(QIcon(":/image/lifeandlist/listbtn_yellow.svg"));
    settingbtn->setIcon(QIcon(":/image/lifeandlist/settingbtn.svg"));
}

void life::settingbtn_push(){
    stackedwidget->setCurrentIndex(2);
    notebtn->setIcon(QIcon(":/image/lifeandlist/notebtn.svg"));
    listbtn->setIcon(QIcon(":/image/lifeandlist/listbtn.svg"));
    settingbtn->setIcon(QIcon(":/image/lifeandlist/settingbtn_yellow.svg"));
}

void life::noteaddbtn_push(){
    stackedwidget->setCurrentIndex(5);
}

void life::listaddbtn_push(){
    stackedwidget->setCurrentIndex(6);
}

bool life::creat_notedatabase_connection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("life.db");
    if(!db.open()){
        qDebug() << "链接笔记and待办数据库失败";
        return false;
    }

    QSqlQuery query;
    bool ret = query.exec("CREATE TABLE IF NOT EXISTS note"
                          "(id INTEGER,"
                          "title NVARCHAR,"
                          "content NVARCHAR,"
                          "createdtime DATATIME,"
                          "updatedtime DATATIME)");
    if(!ret){
        qDebug() << "创建笔记数据表失败";
    }
    return true;
}

