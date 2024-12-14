#include "life.h"
#include "ui_life.h"

life::life(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::life)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);//去掉窗口的标题栏
    creat_notedatabase_connection();
    creat_listdatabase_connection();
    stackedwidget = new QStackedWidget(this);
    stackedwidget->setGeometry(50, 100, 1150, 600);
    initpage();
    initnotepage();
    initlistpage();
    initnotedetailpage();
    initsettingpage();
    initcardwidget();
    initlistwidget();
    initnoteaddpage();
    initlistaddpage();

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

    stackedwidget->addWidget(listpage);//堆叠添加待办页面
    stackedwidget->addWidget(settingpage);//堆叠添加设置页面
    stackedwidget->addWidget(notedetailpage);//堆叠添加日记详情页面
    stackedwidget->addWidget(listdetailpage);//堆叠添加待办详情页面
    stackedwidget->addWidget(noteaddpage);//堆叠日记添加页面
    stackedwidget->addWidget(listaddpage);//堆叠待办添加页面

    notebtn = new QPushButton(this);
    listbtn = new QPushButton(this);
    settingbtn = new QPushButton(this);
    closebtn = new QPushButton(this);
    noteaddbtn = new QPushButton(this);
    listaddbtn = new QPushButton(this);
    listaddbtn->hide();
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

}

void life::initnotepage(){
    //左上状态
    //页面左上角状态初始化
    notestatelabel = new QLabel(this);
    notestatelabel->setText("笔记");
    notestatelabel->setStyleSheet("color:#F6B128");
    QFont font("微软雅黑",30,QFont::Bold);
    notestatelabel->setFont(font);
    notestatelabel->move(70,30);

    //堆叠页面
    QSqlQuery query;
    QString sql = QString("SELECT COUNT(*) FROM note ORDER BY updatedtime DESC");
    int rowCount = 0;
    if (query.exec(sql)) {
        if (query.next()) {
            rowCount = query.value(0).toInt();
            qDebug() << "note中的行数为:" << rowCount;
        }
    } else {
        qDebug() << "查询失败:" ;
    }
    notepageminheight = (rowCount/3+1)*250+50;
    notepage->setMinimumHeight(notepageminheight);

    notescrollArea = new QScrollArea(this);
    notescrollArea->setGeometry(50, 200, 1150, 600);
    notescrollArea->setWidgetResizable(true);
    notescrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    notescrollArea->setStyleSheet("QScrollArea { border: none; }");
    notepage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    notescrollArea->setWidget(notepage);

    stackedwidget->addWidget(notescrollArea);
    stackedwidget->setCurrentWidget(notescrollArea);//设置当前页面索引
}

void life::initlistpage(){
    //左上状态
    //页面左上角状态初始化
    liststatelabel = new QLabel(this);
    liststatelabel->setText("待办");
    liststatelabel->setStyleSheet("color:#F6B128");
    QFont font("微软雅黑",30,QFont::Bold);
    liststatelabel->setFont(font);
    liststatelabel->move(70,30);
    liststatelabel->hide();

    //滚动页面
    //堆叠页面
    QSqlQuery query;
    QString sql = QString("SELECT * FROM list ORDER BY state ASC, updatedtime DESC");
    int rowCount = 0;
    if (query.exec(sql)) {
        if (query.next()) {
            rowCount = query.value(0).toInt();
            qDebug() << "list中的行数为:" << rowCount;
        }
        else rowCount=1;
    } else {
        qDebug() << "查询失败:" ;
    }
    listpageminheight = (rowCount/3+1)*250+50;
    listpage->setMinimumHeight(1000);//暂时修改

    listscrollArea = new QScrollArea(this);
    listscrollArea->setGeometry(50, 200, 1150, 600);
    listscrollArea->setWidgetResizable(true);
    listscrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listscrollArea->setStyleSheet("QScrollArea { border: none; }");
    listpage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listscrollArea->setWidget(listpage);
    stackedwidget->addWidget(listscrollArea);




}

void life::initlistwidget(){
    for(auto listwidget : listwidgets){
        delete listwidget;
    }
    listwidgets.clear();
    QSqlQuery query;
    if(!query.exec("SELECT * FROM list ORDER BY state ASC, updatedtime DESC")){//查询所有列
        qDebug()<<"查询失败";
        return;
    }

    int rowcount = 0;
    while(query.next()){
        int id = query.value(0).toInt();
        QString title = query.value("title").toString();
        int state = query.value(2).toInt();
        QString updatedtime = query.value("updatedtime").toString();
        qDebug()<<id<<" "<<title<<" "<<state<<" "<<updatedtime;
        creatlistwidget(id,title,state,updatedtime,rowcount);
        ++rowcount;
    }
}

void life::initsettingpage(){
    //左上状态
    //页面左上角状态初始化
    settingstatelabel = new QLabel(this);
    settingstatelabel->setText("设置");
    settingstatelabel->setStyleSheet("color:#F6B128");
    QFont font("微软雅黑",30,QFont::Bold);
    settingstatelabel->setFont(font);
    settingstatelabel->move(70,30);
    settingstatelabel->hide();
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
    stackedwidget->setCurrentWidget(notescrollArea);
    notebtn->setIcon(QIcon(":/image/lifeandlist/notebtn_yellow.svg"));
    listbtn->setIcon(QIcon(":/image/lifeandlist/listbtn.svg"));
    settingbtn->setIcon(QIcon(":/image/lifeandlist/settingbtn.svg"));
    noteaddbtn->show();
    listaddbtn->hide();
    notestatelabel->show();
    liststatelabel->hide();
    settingstatelabel->hide();
}

void life::listbtn_push(){
    stackedwidget->setCurrentWidget(listscrollArea);
    notebtn->setIcon(QIcon(":/image/lifeandlist/notebtn.svg"));
    listbtn->setIcon(QIcon(":/image/lifeandlist/listbtn_yellow.svg"));
    settingbtn->setIcon(QIcon(":/image/lifeandlist/settingbtn.svg"));
    listaddbtn->show();
    noteaddbtn->hide();
    liststatelabel->show();
    notestatelabel->hide();
    settingstatelabel->hide();
}

void life::settingbtn_push(){
    stackedwidget->setCurrentWidget(settingpage);
    notebtn->setIcon(QIcon(":/image/lifeandlist/notebtn.svg"));
    listbtn->setIcon(QIcon(":/image/lifeandlist/listbtn.svg"));
    settingbtn->setIcon(QIcon(":/image/lifeandlist/settingbtn_yellow.svg"));
    noteaddbtn->hide();
    listaddbtn->hide();
    settingstatelabel->show();
    notestatelabel->hide();
    liststatelabel->hide();
}

void life::noteaddbtn_push(){
    stackedwidget->setCurrentWidget(noteaddpage);
    qDebug()<<"笔记添加";
}

void life::listaddbtn_push(){
    stackedwidget->setCurrentWidget(listaddpage);
    qDebug()<<"待办添加";
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

bool life::creat_listdatabase_connection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("life.db");
    if(!db.open()){
        qDebug() << "链接笔记and待办数据库失败";
        return false;
    }

    QSqlQuery query;
    bool ret = query.exec("CREATE TABLE IF NOT EXISTS list"
                          "(id INTEGER,"
                          "title NVARCHAR,"
                          "state INTEGER,"
                          "createdtime DATATIME,"
                          "updatedtime DATATIME)");
    if(!ret){
        qDebug() << "创建待办数据表失败";
    }
    return true;
}

void life::initcardwidget(){
    for(auto cardwidget : notecardwidgets){
        delete cardwidget;
    }
    notecardwidgets.clear();
    QSqlQuery query;
    if(!query.exec("SELECT * FROM note ORDER BY updatedtime DESC")){//查询所有列
        qDebug()<<"查询失败";
        return;
    }

    int rowcount = 0;
    while(query.next()){
        int id = query.value(0).toInt();
        QString title = query.value("title").toString();
        QString content = query.value("content").toString();
        QString updatedtime = query.value("updatedtime").toString();
        qDebug()<<id<<" "<<title<<" "<<content<<" "<<updatedtime;
        creatnotecardwidget(id,title,content,updatedtime,rowcount);

        ++rowcount;
    }
}

void life::creatnotecardwidget(int id,QString title,QString content,QString updatedtime,int rowcount)
{
    int columncount = rowcount/3;
    int columnindex = rowcount%3;
    CardWidget *cardwidget = new CardWidget(notepage);
    notecardwidgets.append(cardwidget);
    cardwidget->setid(id);
    cardwidget->settitle(title);
    cardwidget->setcontent(content);
    cardwidget->settime(updatedtime);
    cardwidget->move(50+columnindex*345,10+columncount*245);
    cardwidget->show();

    connect(cardwidget,&CardWidget::clicked,notepage,[this](int id){
        notecard_push(id);
    });
}

void life::creatlistwidget(int id,QString title,int state,QString updatedtime,int rowcount){
    listwidget *list = new listwidget(listpage);
    listwidgets.append(list);
    list->setid(id);
    list->setlabelunchecked();
    if(state==1) list->setlabelchecked();
    list->settitle(title);
    list->move(30,70*rowcount);
    list->show();

    connect(list,&listwidget::getcheckboxstatement,this,&life::changecheckboxstate);
    connect(list,&listwidget::getdeleteaction,this,&life::receivelistdeleteaction);

}

void life::notecard_push(int id){
    qDebug()<<id;
    notedetail(id);
}

void life::notedetail(int widgetid){
    stackedwidget->setCurrentWidget(notedetailpage);
    notedetailpage->show();
    noteaddbtn->hide();
    listaddbtn->hide();

    //读取数据
    QString title;
    QString content;
    QString updatedtime;
    QSqlQuery query;
    if(!query.exec("SELECT * FROM note")){//查询所有列
        qDebug()<<"查询失败";
        return;
    }
    while(query.next()){
        int id = query.value(0).toInt();
        if(id == widgetid){
            title = query.value(1).toString();
            content = query.value(2).toString();
            QString time = query.value(4).toString();
            updatedtime = time;
            qDebug()<<"找到数据"<<updatedtime;
            break;
        }
    }

    notedetail_id_label->setText(QString::number(widgetid));
    titleEdit->setText(title);
    timelabel->setText(updatedtime);
    contentedit->setText(content);
    qDebug()<<timelabel->text();

}




void life::initnotedetailpage(){
    QPushButton *notesavebtn = new QPushButton(notedetailpage);
    notesavebtn->setIcon(QIcon(":/image/lifeandlist/savebtn.svg"));
    notesavebtn->move(1050,70);
    notesavebtn->setIconSize(QSize(35,35));
    notesavebtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                               "QPushButton:hover { background-color: #f0f0f0; }");
    notesavebtn->show();

    notereturnbtn = new QPushButton(notedetailpage);
    notereturnbtn->setIcon(QIcon(":/image/lifeandlist/returnbtn.svg"));
    notereturnbtn->move(1000,70);
    notereturnbtn->setIconSize(QSize(40,40));
    notereturnbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                                 "QPushButton:hover { background-color: #f0f0f0; }");
    notereturnbtn->show();

    notedeletebtn = new QPushButton(notedetailpage);
    notedeletebtn->setIcon(QIcon(":/image/lifeandlist/deletebtn.svg"));
    notedeletebtn->move(1100,67);
    notedeletebtn->setIconSize(QSize(40,40));
    notedeletebtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                                 "QPushButton:hover { background-color: #f0f0f0; }");
    notedeletebtn->show();

    //信号与槽
    connect(notereturnbtn,&QPushButton::clicked,this,&life::updatenotecard);
    connect(notedeletebtn,&QPushButton::clicked,this,&life::notedeletebtn_push);
    connect(notesavebtn,&QPushButton::clicked,this,&life::notesavebtn_push);

    //标题
    titleEdit = new QLineEdit(notedetailpage);
    titleEdit->setStyleSheet("color:#F6B128;border:none;");
    QFont titlefont("微软雅黑",30,QFont::Bold);
    titleEdit->setFont(titlefont);
    titleEdit->move(30,10);
    titleEdit->show();
    //时间
    timelabel = new QLabel(notedetailpage);
    timelabel->setStyleSheet("color:grey;");
    QFont timefont("微软雅黑",10,QFont::Bold);
    timelabel->setFont(timefont);
    timelabel->setFixedWidth(500);
    timelabel->move(30,80);
    timelabel->show();
    //内容
    contentedit = new QTextEdit(notedetailpage);
    contentedit->setStyleSheet("background-color:#F9F9FB;border:none;border-radius:25px");
    QFont contentfont("楷体",18,QFont::Bold);
    contentedit->setFont(contentfont);
    contentedit->move(30,120);
    contentedit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    contentedit->setFixedSize(QSize(1100,700));
    contentedit->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    contentedit->show();

    //隐形idlabel
    notedetail_id_label = new QLabel(notedetailpage);
    notedetail_id_label->hide();

}

void life::notedeletebtn_push(){
    int id = notedetail_id_label->text().toInt();
    QSqlQuery query;

    if(!query.exec("SELECT * FROM note")){//查询所有列
        qDebug()<<"查找数据库失败！";
        return;
    }
    query.prepare("DELETE FROM note WHERE id=:value");
    query.bindValue(":value",id);
    if(!query.exec()){
        qDebug()<<"删除失败";
        QMessageBox::warning(this,"警告","删除失败！");
    }
    else{
        qDebug()<<"删除成功!";
        QMessageBox::warning(this,"祝贺","删除成功！");
    }
    updatenotecard();
}

void life::notesavebtn_push(){
    int id = notedetail_id_label->text().toInt();
    QString newtitle = titleEdit->text();
    QString newcontent = contentedit->toHtml();
    QString currenttime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    QSqlQuery query;
    QString sql = "UPDATE note SET title = :title,content = :content,updatedtime = :updatedtime WHERE id = :id";
    query.prepare(sql);
    query.bindValue(":id",id);
    query.bindValue(":title",newtitle);
    query.bindValue(":content",newcontent);
    query.bindValue(":updatedtime",currenttime);
    if(query.exec()){
        QMessageBox::warning(this,"恭喜","修改成功");
    }
    else{
        QMessageBox::warning(this,"警告","修改失败！");
    }

}

void life::initnoteaddpage(){
    noteaddpage_returnbtn = new QPushButton(noteaddpage);
    noteaddpage_savebtn = new QPushButton(noteaddpage);
    noteaddpage_titleEdit = new QLineEdit(noteaddpage);
    noteaddpage_contentedit = new QTextEdit(noteaddpage);

    //标题
    noteaddpage_titleEdit->setText("请输入标题");
    noteaddpage_titleEdit->setStyleSheet("color:#F6B128;border:none;");
    QFont titlefont("微软雅黑",30,QFont::Bold);
    noteaddpage_titleEdit->setFont(titlefont);
    noteaddpage_titleEdit->move(30,10);
    noteaddpage_titleEdit->show();

    //内容
    noteaddpage_contentedit->setStyleSheet("background-color:#F9F9FB;border:none;border-radius:25px");
    noteaddpage_contentedit->setText("请输入笔记内容");
    QFont contentfont("楷体",18,QFont::Bold);
    noteaddpage_contentedit->setFont(contentfont);
    noteaddpage_contentedit->move(30,110);
    noteaddpage_contentedit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    noteaddpage_contentedit->setFixedSize(QSize(1100,700));
    noteaddpage_contentedit->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    noteaddpage_contentedit->show();

    //保存按钮
    noteaddpage_savebtn->setIcon(QIcon(":/image/lifeandlist/savebtn.svg"));
    noteaddpage_savebtn->move(1050,70);
    noteaddpage_savebtn->setIconSize(QSize(35,35));
    noteaddpage_savebtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                               "QPushButton:hover { background-color: #f0f0f0; }");
    noteaddpage_savebtn->show();

    //返回按钮
    noteaddpage_returnbtn->setIcon(QIcon(":/image/lifeandlist/returnbtn.svg"));
    noteaddpage_returnbtn->move(1000,70);
    noteaddpage_returnbtn->setIconSize(QSize(40,40));
    noteaddpage_returnbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                                 "QPushButton:hover { background-color: #f0f0f0; }");
    noteaddpage_returnbtn->show();

    noteaddpage->show();

    //信号与槽
    connect(noteaddpage_returnbtn,&QPushButton::clicked,this,&life::updatenotecard);
    connect(noteaddpage_savebtn,&QPushButton::clicked,this,&life::noteaddpage_savebtn_push);

}

void life::noteaddpage_savebtn_push(){
    QSqlQuery query;
    if(!query.exec("SELECT * FROM note")){//查询所有列
        qDebug()<<"添加失败";
        return;
    }
    int id[1000]={0};
    while(query.next()){
        id[query.value(0).toInt()]++;
    }

    query.prepare("INSERT INTO note (id,title,content,createdtime,updatedtime) VALUES (:id,:title,:content,:createdtime,:updatedtime)");
    for(int i = 1;i<=999;i++){
        if(!id[i]){
            query.bindValue(":id",i);
            break;
        }
    }

    query.bindValue(":title",noteaddpage_titleEdit->text());
    query.bindValue(":content",noteaddpage_contentedit->toHtml());
    query.bindValue(":createdtime",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":updatedtime",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if (!query.exec()) {
        qDebug() << "插入数据错误 ";
    } else {
        QMessageBox::warning(this,"祝贺","新建笔记成功！");
        qDebug() << "插入数据成功!";
        noteaddpage_titleEdit->setText("请输入标题");
        noteaddpage_contentedit->setText("请输入笔记内容");
        updatenotecard();
    }
}


void life::initlistaddpage(){
    listaddpage_lineEdit = new QLineEdit(listaddpage);
    listaddpage_comfirmbtn = new QPushButton(listaddpage);
    //输入框
    listaddpage_lineEdit->move(100,200);
    listaddpage_lineEdit->setFixedWidth(900);
    listaddpage_lineEdit->setMinimumHeight(100);
    listaddpage_lineEdit->setStyleSheet("background-color:#F9F9FB;border:none;border-radius:25px;font-size:30px;color:#F6B128;");
    listaddpage_lineEdit->setText("请输入待办事项");
    //确认按钮
    listaddpage_comfirmbtn->setIcon(QIcon(":/image/lifeandlist/confirmbtn.svg"));
    listaddpage_comfirmbtn->setIconSize(QSize(80,80));
    listaddpage_comfirmbtn->move(500,400);
    listaddpage_comfirmbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                                       "QPushButton:hover { background-color: #f0f0f0; }");
    //信号与槽
    connect(listaddpage_comfirmbtn,&QPushButton::clicked,this,&life::listaddpage_comfirmbtn_push);



}

void life::listaddpage_comfirmbtn_push(){
    QSqlQuery query;
    if(!query.exec("SELECT * FROM list")){//查询所有列
        qDebug()<<"添加失败";
        return;
    }
    int id[1000]={0};
    while(query.next()){
        id[query.value(0).toInt()]++;
    }

    query.prepare("INSERT INTO list (id,title,state,createdtime,updatedtime) VALUES (:id,:title,:state,:createdtime,:updatedtime)");
    for(int i = 1;i<=999;i++){
        if(!id[i]){
            query.bindValue(":id",i);
            break;
        }
    }

    query.bindValue(":title",listaddpage_lineEdit->text());
    query.bindValue(":state",0);
    query.bindValue(":createdtime",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":updatedtime",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if (!query.exec()) {
        qDebug() << "插入数据错误 ";
    } else {
        QMessageBox::warning(this,"祝贺","新建待办成功！");
        qDebug() << "插入数据成功!";
        listaddpage_lineEdit->setText("请输入待办");
        updatelistwidget();
    }
}

void life::updatenotecard(){

    stackedwidget->setCurrentWidget(notescrollArea);
    noteaddbtn->show();
    qDebug()<<"更新笔记数据";
    for(auto cardwidget : notecardwidgets){
        delete cardwidget;
    }
    notecardwidgets.clear();
    qDebug()<<"删除成功";
    QSqlQuery query;
    if(!query.exec("SELECT * FROM note ORDER BY updatedtime DESC")){//查询所有列
        qDebug()<<"查询失败";
        return;
    }

    int rowcount = 0;
    while(query.next()){
        int id = query.value(0).toInt();
        QString title = query.value("title").toString();
        QString content = query.value("content").toString();
        QString updatedtime = query.value("updatedtime").toString();
        qDebug()<<id<<" "<<title<<" "<<content<<" "<<updatedtime;
        creatnotecardwidget(id,title,content,updatedtime,rowcount);
        ++rowcount;
    }
}

void life::updatelistwidget(){
    stackedwidget->setCurrentWidget(listscrollArea);
    listaddbtn->show();

    for(auto listwidget : listwidgets){
        listwidget->deleteLater();
    }

    listwidgets.clear();
    QSqlQuery query;
    if(!query.exec("SELECT * FROM list ORDER BY state ASC, updatedtime DESC")){//查询所有列
        qDebug()<<"查询失败";
        return;
    }

    int rowcount = 0;
    while(query.next()){
        int id = query.value(0).toInt();
        QString title = query.value("title").toString();
        int state = query.value(2).toInt();
        QString updatedtime = query.value("updatedtime").toString();
        qDebug()<<id<<" "<<title<<" "<<state<<" "<<updatedtime;
        creatlistwidget(id,title,state,updatedtime,rowcount);
        ++rowcount;
    }
}

void life::changecheckboxstate(int state,int id){
    QSqlQuery query;
    QString sql = "UPDATE list SET state = :state WHERE id == :id";
    query.prepare(sql);
    query.bindValue(":state",state);
    query.bindValue(":id",id);
    qDebug()<<id;
    if(!query.exec()){
        qDebug()<<"未查找到";
    }
    else{
        qDebug()<<"状态修改成功";
    }
    updatelistwidget();
}

void life::receivelistdeleteaction(int id){
    deletelist(id);
}

void life::deletelist(int id){
    QSqlQuery query;
    QString sql = "DELETE FROM list WHERE id=:id";
    query.prepare(sql);
    query.bindValue(":id",id);
    qDebug()<<id;
    if(!query.exec()){
        qDebug()<<"未查找到";
    }
    else{
        qDebug()<<"删除成功";
    }
    updatelistwidget();
}


