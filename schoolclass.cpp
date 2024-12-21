#include "schoolclass.h"
#include "ui_schoolclass.h"

schoolclass::schoolclass(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::schoolclass)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);//去掉窗口的标题栏
    stackedwidget = new QStackedWidget(this);
    stackedwidget->move(150,130);
    stackedwidget->resize(1450,1040);
    create_database_connection();
    initdatecount();
    initpage();


}

schoolclass::~schoolclass()
{
    delete ui;
}

bool schoolclass::create_database_connection(){
    classdb = QSqlDatabase::addDatabase("QSQLITE","classconnection");
    classdb.setDatabaseName("class.db");
    if(!classdb.open()){
        qDebug() << "链接课程数据库失败";
        return false;
    }

    QSqlQuery query(classdb);
    bool ret = query.exec("CREATE TABLE IF NOT EXISTS class"
                          "(courseid INTEGER,"
                          "coursename NVARCHAR,"
                          "teachername NVARCHAR,"
                          "courseplace NVARCHAR,"
                          "week1 INTEGER DEFAULT 0,"
                          "week2 INTEGER DEFAULT 0,"
                          "week3 INTEGER DEFAULT 0,"
                          "week4 INTEGER DEFAULT 0,"
                          "week5 INTEGER DEFAULT 0,"
                          "week6 INTEGER DEFAULT 0,"
                          "week7 INTEGER DEFAULT 0,"
                          "week8 INTEGER DEFAULT 0,"
                          "week9 INTEGER DEFAULT 0,"
                          "week10 INTEGER DEFAULT 0,"
                          "week11 INTEGER DEFAULT 0,"
                          "week12 INTEGER DEFAULT 0,"
                          "week13 INTEGER DEFAULT 0,"
                          "week14 INTEGER DEFAULT 0,"
                          "week15 INTEGER DEFAULT 0,"
                          "week16 INTEGER DEFAULT 0,"
                          "week17 INTEGER DEFAULT 0,"
                          "week18 INTEGER DEFAULT 0,"
                          "week19 INTEGER DEFAULT 0,"
                          "week20 INTEGER DEFAULT 0,"
                          "week21 INTEGER DEFAULT 0,"
                          "week22 INTEGER DEFAULT 0,"
                          "week23 INTEGER DEFAULT 0,"
                          "week24 INTEGER DEFAULT 0,"
                          "week25 INTEGER DEFAULT 0,"
                          "coursenumber1 INTEGER DEFAULT 0,"
                          "coursenumber2 INTEGER DEFAULT 0,"
                          "coursenumber3 INTEGER DEFAULT 0,"
                          "coursenumber4 INTEGER DEFAULT 0,"
                          "coursenumber5 INTEGER DEFAULT 0,"
                          "coursenumber6 INTEGER DEFAULT 0,"
                          "coursenumber7 INTEGER DEFAULT 0,"
                          "coursenumber8 INTEGER DEFAULT 0,"
                          "coursenumber9 INTEGER DEFAULT 0,"
                          "coursenumber10 INTEGER DEFAULT 0,"
                          "coursenumber11 INTEGER DEFAULT 0,"
                          "coursenumber12 INTEGER DEFAULT 0,"
                          "coursenumber13 INTEGER DEFAULT 0,"
                          "coursenumber14 INTEGER DEFAULT 0,"
                          "coursenumber15 INTEGER DEFAULT 0,"
                          "coursenumber16 INTEGER DEFAULT 0,"
                          "monday INTEGER DEFAULT 0,"
                          "tuesday INTEGER DEFAULT 0,"
                          "wednesday INTEGER DEFAULT 0,"
                          "thursday INTEGER DEFAULT 0,"
                          "friday INTEGER DEFAULT 0,"
                          "saturday INTEGER DEFAULT 0,"
                          "sunday INTEGER DEFAULT 0)");
    if(!ret){
        qDebug() << "创建课程表数据表失败";
    }
    else qDebug()<<"课程表数据表创建成功";

    return true;
}

void schoolclass::initdatecount(){
    QSettings cfg("classconfig.ini", QSettings::IniFormat);
    initdate = cfg.value("selectedDate").toDate();
    currentdate = QDate::currentDate();
    daydifference = initdate.daysTo(currentdate);
    qDebug()<<"日期差"<<initdate<<daydifference;
    currentweeknumber = daydifference/7+1;
    currentweekcount = currentweeknumber;
}


void schoolclass::initpage(){
    //new页面
    addpage = new QWidget(this);
    settingpage = new QWidget(this);
    coursedetailpage = new QWidget(this);
    week1page = new QWidget(this);
    week2page = new QWidget(this);
    week3page = new QWidget(this);
    week4page = new QWidget(this);
    week5page = new QWidget(this);
    week6page = new QWidget(this);
    week7page = new QWidget(this);
    week8page = new QWidget(this);
    week9page = new QWidget(this);
    week10page = new QWidget(this);
    week11page = new QWidget(this);
    week12page = new QWidget(this);
    week13page = new QWidget(this);
    week14page = new QWidget(this);
    week15page = new QWidget(this);
    week16page = new QWidget(this);
    week17page = new QWidget(this);
    week18page = new QWidget(this);
    week19page = new QWidget(this);
    week20page = new QWidget(this);
    week21page = new QWidget(this);
    week22page = new QWidget(this);
    week23page = new QWidget(this);
    week24page = new QWidget(this);
    week25page = new QWidget(this);
    //添加进入vector容器
    weekpages.append(week1page);
    weekpages.append(week2page);
    weekpages.append(week3page);
    weekpages.append(week4page);
    weekpages.append(week5page);
    weekpages.append(week6page);
    weekpages.append(week7page);
    weekpages.append(week8page);
    weekpages.append(week9page);
    weekpages.append(week10page);
    weekpages.append(week11page);
    weekpages.append(week12page);
    weekpages.append(week13page);
    weekpages.append(week14page);
    weekpages.append(week15page);
    weekpages.append(week16page);
    weekpages.append(week17page);
    weekpages.append(week18page);
    weekpages.append(week19page);
    weekpages.append(week20page);
    weekpages.append(week21page);
    weekpages.append(week22page);
    weekpages.append(week23page);
    weekpages.append(week24page);
    weekpages.append(week25page);

    //设置页面大小
    for(auto weekpage : weekpages){
        weekpage->setFixedSize(QSize(1800,1200));
    }
    //堆叠页面添加
    stackedwidget->addWidget(addpage);
    for(auto weekpage : weekpages){
        stackedwidget->addWidget(weekpage);
    }
    stackedwidget->addWidget(settingpage);
    stackedwidget->addWidget(coursedetailpage);
    //初始化每个weekpage
    for(auto weekpage : weekpages){
        initweekpage(weekpage);
    }

    stackedwidget->setCurrentIndex(currentweekcount);
    //其他page
    initupperpage();
    initcoursetabel_upper_left();
    inittable();
    initweekpage();
    initaddpage();
    initsettingpage();
}

void schoolclass::initupperpage(){
    leftbtn = new QPushButton(this);
    rightbtn = new QPushButton(this);
    addbtn = new QPushButton(this);
    settingbtn = new QPushButton(this);
    closebtn = new QPushButton(this);
    weeklabel = new QLabel(this);
    currentweeklabel = new QLabel(this);

    leftbtn->setIcon(QIcon(":/image/class/leftbtn.svg"));
    rightbtn->setIcon(QIcon(":/image/class/rightbtn.svg"));
    addbtn->setIcon(QIcon(":/image/class/addbtn.svg"));
    settingbtn->setIcon(QIcon(":/image/class/settingbtn.svg"));
    closebtn->setIcon(QIcon(":/image/class/closebtn.svg"));

    leftbtn->setIconSize(QSize(50,50));
    rightbtn->setIconSize(QSize(50,50));
    addbtn->setIconSize(QSize(50,50));
    settingbtn->setIconSize(QSize(50,50));
    closebtn->setIconSize(QSize(50,50));


    weeklabel->move(window_width*0.4,0);
    closebtn->move(window_width-50,15);
    settingbtn->move(window_width*0.75,15);
    addbtn->move(window_width*0.75-60,15);
    leftbtn->move(window_width*0.4-100,15);
    rightbtn->move(window_width*0.4+200,15);
    currentweeklabel->move(window_width*0.45-20,60);
    //按钮样式
    settingbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                              "QPushButton:hover { background-color: #f0f0f0; }");
    closebtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                            "QPushButton:hover { background-color: #f0f0f0; }");
    addbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                           "QPushButton:hover { background-color: #f0f0f0; }");
    leftbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                           "QPushButton:hover { background-color: #f0f0f0; }");
    rightbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                              "QPushButton:hover { background-color: #f0f0f0; }");
    //label样式
    weeklabel->setStyleSheet("color:#F6B128");
    QFont font1("微软雅黑",30,QFont::Bold);
    weeklabel->setFont(font1);
    weeklabel->setMinimumWidth(200);
    currentweeklabel->setStyleSheet("color:#F6B128");
    QFont font2("微软雅黑",12,QFont::Bold);
    currentweeklabel->setFont(font2);
    currentweeklabel->setMinimumWidth(150);

    //weeklabel
    QString weekstring = "第"+QString::number(currentweekcount)+"周";
    weeklabel->setText(weekstring);
    stackedwidget->setCurrentIndex(currentweekcount);

    //信号与槽
    connect(closebtn,&QPushButton::clicked,this,&schoolclass::closebtn_push);
    connect(leftbtn,&QPushButton::clicked,this,&schoolclass::leftbtn_push);
    connect(rightbtn,&QPushButton::clicked,this,&schoolclass::rightbtn_push);
    connect(addbtn,&QPushButton::clicked,this,&schoolclass::addbtn_push);
    connect(settingbtn,&QPushButton::clicked,this,&schoolclass::settingbtn_push);
    //缺乏功能：点击currentweeklabel回到对应周
}

void schoolclass::initcoursetabel_upper_left(){
    //上侧
    monday = new QLabel(this);
    tuesday = new QLabel(this);
    wednesday = new QLabel(this);
    thursday = new QLabel(this);
    friday = new QLabel(this);
    saturday = new QLabel(this);
    sunday = new QLabel(this);

    QFont font("微软雅黑",12,QFont::Bold);

    monday->setText("星期一");
    tuesday->setText("星期二");
    wednesday->setText("星期三");
    thursday->setText("星期四");
    friday->setText("星期五");
    saturday->setText("星期六");
    sunday->setText("星期天");

    monday->setFont(font);
    tuesday->setFont(font);
    wednesday->setFont(font);
    thursday->setFont(font);
    friday->setFont(font);
    saturday->setFont(font);
    sunday->setFont(font);

    monday->setMinimumWidth(150);
    tuesday->setMinimumWidth(150);
    wednesday->setMinimumWidth(150);
    thursday->setMinimumWidth(150);
    friday->setMinimumWidth(150);
    saturday->setMinimumWidth(150);
    sunday->setMinimumWidth(150);

    monday->move(uppertabel_x, uppertabel_y);
    tuesday->move(uppertabel_x + uppertabel_hinterval * 1, uppertabel_y);
    wednesday->move(uppertabel_x + uppertabel_hinterval * 2, uppertabel_y);
    thursday->move(uppertabel_x + uppertabel_hinterval * 3, uppertabel_y);
    friday->move(uppertabel_x + uppertabel_hinterval * 4, uppertabel_y);
    saturday->move(uppertabel_x + uppertabel_hinterval * 5, uppertabel_y);
    sunday->move(uppertabel_x + uppertabel_hinterval * 6, uppertabel_y);



    // 左侧
    coursenum1 = new QLabel(this);
    coursenum2 = new QLabel(this);
    coursenum3 = new QLabel(this);
    coursenum4 = new QLabel(this);
    coursenum5 = new QLabel(this);
    coursenum6 = new QLabel(this);
    coursenum7 = new QLabel(this);
    coursenum8 = new QLabel(this);
    coursenum9 = new QLabel(this);
    coursenum10 = new QLabel(this);
    coursenum11 = new QLabel(this);
    coursenum12 = new QLabel(this);
    coursenum13 = new QLabel(this);

    coursenum1->setText("第一节");
    coursenum2->setText("第二节");
    coursenum3->setText("第三节");
    coursenum4->setText("第四节");
    coursenum5->setText("第五节");
    coursenum6->setText("第六节");
    coursenum7->setText("第七节");
    coursenum8->setText("第八节");
    coursenum9->setText("第九节");
    coursenum10->setText("第十节");
    coursenum11->setText("第十一节");
    coursenum12->setText("第十二节");
    coursenum13->setText("第十三节");

    coursenum1->setFont(font);
    coursenum2->setFont(font);
    coursenum3->setFont(font);
    coursenum4->setFont(font);
    coursenum5->setFont(font);
    coursenum6->setFont(font);
    coursenum7->setFont(font);
    coursenum8->setFont(font);
    coursenum9->setFont(font);
    coursenum10->setFont(font);
    coursenum11->setFont(font);
    coursenum12->setFont(font);
    coursenum13->setFont(font);

    coursenum1->setMinimumWidth(100);
    coursenum2->setMinimumWidth(100);
    coursenum3->setMinimumWidth(100);
    coursenum4->setMinimumWidth(100);
    coursenum5->setMinimumWidth(100);
    coursenum6->setMinimumWidth(100);
    coursenum7->setMinimumWidth(100);
    coursenum8->setMinimumWidth(100);
    coursenum9->setMinimumWidth(100);
    coursenum10->setMinimumWidth(100);
    coursenum11->setMinimumWidth(100);
    coursenum12->setMinimumWidth(100);
    coursenum13->setMinimumWidth(100);

    coursenum1->move(lefttable_x, lefttable_y);
    coursenum2->move(lefttable_x, lefttable_y + lefttable_vinterval * 1);
    coursenum3->move(lefttable_x, lefttable_y + lefttable_vinterval * 2);
    coursenum4->move(lefttable_x, lefttable_y + lefttable_vinterval * 3);
    coursenum5->move(lefttable_x, lefttable_y + lefttable_vinterval * 4);
    coursenum6->move(lefttable_x, lefttable_y + lefttable_vinterval * 5);
    coursenum7->move(lefttable_x, lefttable_y + lefttable_vinterval * 6);
    coursenum8->move(lefttable_x, lefttable_y + lefttable_vinterval * 7);
    coursenum9->move(lefttable_x, lefttable_y + lefttable_vinterval * 8);
    coursenum10->move(lefttable_x, lefttable_y + lefttable_vinterval * 9);
    coursenum11->move(lefttable_x-10, lefttable_y + lefttable_vinterval * 10);
    coursenum12->move(lefttable_x-10, lefttable_y + lefttable_vinterval * 11);
    coursenum13->move(lefttable_x-10, lefttable_y + lefttable_vinterval * 12);

}

void schoolclass::inittable(){
    table1 = new coursetabelwidget(week1page);
    table2 = new coursetabelwidget(week2page);
    table3 = new coursetabelwidget(week3page);
    table4 = new coursetabelwidget(week4page);
    table5 = new coursetabelwidget(week5page);
    table6 = new coursetabelwidget(week6page);
    table7 = new coursetabelwidget(week7page);
    table8 = new coursetabelwidget(week8page);
    table9 = new coursetabelwidget(week9page);
    table10 = new coursetabelwidget(week10page);
    table11 = new coursetabelwidget(week11page);
    table12 = new coursetabelwidget(week12page);
    table13 = new coursetabelwidget(week13page);
    table14 = new coursetabelwidget(week14page);
    table15 = new coursetabelwidget(week15page);
    table16 = new coursetabelwidget(week16page);
    table17 = new coursetabelwidget(week17page);
    table18 = new coursetabelwidget(week18page);
    table19 = new coursetabelwidget(week19page);
    table20 = new coursetabelwidget(week20page);
    table21 = new coursetabelwidget(week21page);
    table22 = new coursetabelwidget(week22page);
    table23 = new coursetabelwidget(week23page);
    table24 = new coursetabelwidget(week24page);
    table25 = new coursetabelwidget(week25page);

    tables[1] = table1;
    tables[2] = table2;
    tables[3] = table3;
    tables[4] = table4;
    tables[5] = table5;
    tables[6] = table6;
    tables[7] = table7;
    tables[8] = table8;
    tables[9] = table9;
    tables[10] = table10;
    tables[11] = table11;
    tables[12] = table12;
    tables[13] = table13;
    tables[14] = table14;
    tables[15] = table15;
    tables[16] = table16;
    tables[17] = table17;
    tables[18] = table18;
    tables[19] = table19;
    tables[20] = table20;
    tables[21] = table21;
    tables[22] = table22;
    tables[23] = table23;
    tables[24] = table24;
    tables[25] = table25;

    //初始化coursecard信号与槽
    for(auto table : tables){
        for(auto coursecard : table->coursecards){
            connect(coursecard,&coursecard::geteditaction,this,&schoolclass::editcourse);
            connect(coursecard,&coursecard::getdeletethisaction,this,&schoolclass::deletethiscourse);
            connect(coursecard,&coursecard::getdeleteallaction,this,&schoolclass::deleteallthiscourse);
        }
    }
}

void schoolclass::initweekpage(){
    //清空原有信息
    for(int i = 1;i<=25;i++){
        for(int j = 1;j<=91;j++){
            tables[i]->setcoursecard(j,0,0,"","");
        }
    }

    //添加新信息
    for(int i = 1;i<=25;i++){
        int day = 0;
        QVector<int> coursenumber;
        coursenumber.clear();
        QSqlQuery query(classdb);
        QString weekcolumn = "week"+QString::number(i);
        QString sql = "SELECT * FROM class WHERE "+weekcolumn+"=1";
        query.prepare(sql);
        if (!query.exec()) {
            qDebug() << "查询失败:" << query.lastError();
        } else {
            qDebug()<<"查询课程表成功";
            while(query.next()){
                qDebug()<<"进入循环";
                coursenumber.clear();
                QString coursename;
                QString courseteacher;
                QString courselocation;
                int courseid;

                coursename = query.value("coursename").toString();
                courseteacher = query.value("teachername").toString();
                courselocation = query.value("courseplace").toString();
                courseid = query.value("courseid").toInt();
                //每天的第几节课
                for(int j = 1;j<=13;j++){
                    QString coursenumberstring = "coursenumber"+QString::number(j);
                    if(query.value(coursenumberstring)==1){
                        coursenumber.push_back(j);
                    }

                }
                //星期几，只能取一天
                if (query.value("monday")==1) day = 1;
                else if (query.value("tuesday")==1) day = 2;
                else if (query.value("wednesday")==1) day = 3;
                else if (query.value("thursday")==1) day = 4;
                else if (query.value("friday")==1) day = 5;
                else if (query.value("saturday")==1) day = 6;
                else if (query.value("sunday")==1) day = 7;

                //在对应的页面对应的卡片设置对应的信息
                for(int course : coursenumber){
                    qDebug()<<course<<" "<<courseid<<" "<<coursename<<" "<<courseteacher;
                    tables[i]->setcoursecard((day-1)*13+course,courseid,i,coursename,courseteacher+" "+courselocation);
                }

            }
        }

    }
}

void schoolclass::initaddpage(){
    coursenamelabel = new QLabel(addpage);
    teachernamelabel = new QLabel(addpage);
    courselocationlabel = new QLabel(addpage);
    addpage_weeklabel = new QLabel(addpage);
    addpage_coursenumlabel = new QLabel(addpage);
    addpage_daylabel = new QLabel(addpage);
    addpage_coursenameedit = new QLineEdit(addpage);
    addpage_teachernameedit = new QLineEdit(addpage);
    addpage_courselocationedit = new QLineEdit(addpage);
    addpage_comfirmbtn = new QPushButton(addpage);
    addpage_savebtn = new QPushButton(addpage);

    coursenamelabel->setText("课程名称:");
    teachernamelabel->setText("授课人:");
    courselocationlabel->setText("授课地点:");
    addpage_weeklabel->setText("周数");
    addpage_coursenumlabel->setText("节数");
    addpage_daylabel->setText("星期");


    QFont font1("微软雅黑",20,QFont::Bold);
    QFont font2("微软雅黑",16,QFont::Bold);
    coursenamelabel->setFont(font1);
    teachernamelabel->setFont(font1);
    courselocationlabel->setFont(font1);
    addpage_weeklabel->setFont(font2);
    addpage_coursenumlabel->setFont(font2);
    addpage_daylabel->setFont(font2);
    coursenamelabel->setMinimumWidth(200);
    teachernamelabel->setMinimumWidth(200);
    courselocationlabel->setMinimumWidth(200);
    addpage_weeklabel->setMinimumWidth(200);
    addpage_coursenumlabel->setMinimumWidth(200);
    addpage_daylabel->setMinimumWidth(200);

    //25周复选按钮
    addpage_week1btn = new QCheckBox(addpage);
    addpage_week2btn = new QCheckBox(addpage);
    addpage_week3btn = new QCheckBox(addpage);
    addpage_week4btn = new QCheckBox(addpage);
    addpage_week5btn = new QCheckBox(addpage);
    addpage_week6btn = new QCheckBox(addpage);
    addpage_week7btn = new QCheckBox(addpage);
    addpage_week8btn = new QCheckBox(addpage);
    addpage_week9btn = new QCheckBox(addpage);
    addpage_week10btn = new QCheckBox(addpage);
    addpage_week11btn = new QCheckBox(addpage);
    addpage_week12btn = new QCheckBox(addpage);
    addpage_week13btn = new QCheckBox(addpage);
    addpage_week14btn = new QCheckBox(addpage);
    addpage_week15btn = new QCheckBox(addpage);
    addpage_week16btn = new QCheckBox(addpage);
    addpage_week17btn = new QCheckBox(addpage);
    addpage_week18btn = new QCheckBox(addpage);
    addpage_week19btn = new QCheckBox(addpage);
    addpage_week20btn = new QCheckBox(addpage);
    addpage_week21btn = new QCheckBox(addpage);
    addpage_week22btn = new QCheckBox(addpage);
    addpage_week23btn = new QCheckBox(addpage);
    addpage_week24btn = new QCheckBox(addpage);
    addpage_week25btn = new QCheckBox(addpage);

    weekbtns[1] = addpage_week1btn;
    weekbtns[2] = addpage_week2btn;
    weekbtns[3] = addpage_week3btn;
    weekbtns[4] = addpage_week4btn;
    weekbtns[5] = addpage_week5btn;
    weekbtns[6] = addpage_week6btn;
    weekbtns[7] = addpage_week7btn;
    weekbtns[8] = addpage_week8btn;
    weekbtns[9] = addpage_week9btn;
    weekbtns[10] = addpage_week10btn;
    weekbtns[11] = addpage_week11btn;
    weekbtns[12] = addpage_week12btn;
    weekbtns[13] = addpage_week13btn;
    weekbtns[14] = addpage_week14btn;
    weekbtns[15] = addpage_week15btn;
    weekbtns[16] = addpage_week16btn;
    weekbtns[17] = addpage_week17btn;
    weekbtns[18] = addpage_week18btn;
    weekbtns[19] = addpage_week19btn;
    weekbtns[20] = addpage_week20btn;
    weekbtns[21] = addpage_week21btn;
    weekbtns[22] = addpage_week22btn;
    weekbtns[23] = addpage_week23btn;
    weekbtns[24] = addpage_week24btn;
    weekbtns[25] = addpage_week25btn;

    addpage_week1btn->setText("1");
    addpage_week2btn->setText("2");
    addpage_week3btn->setText("3");
    addpage_week4btn->setText("4");
    addpage_week5btn->setText("5");
    addpage_week6btn->setText("6");
    addpage_week7btn->setText("7");
    addpage_week8btn->setText("8");
    addpage_week9btn->setText("9");
    addpage_week10btn->setText("10");
    addpage_week11btn->setText("11");
    addpage_week12btn->setText("12");
    addpage_week13btn->setText("13");
    addpage_week14btn->setText("14");
    addpage_week15btn->setText("15");
    addpage_week16btn->setText("16");
    addpage_week17btn->setText("17");
    addpage_week18btn->setText("18");
    addpage_week19btn->setText("19");
    addpage_week20btn->setText("20");
    addpage_week21btn->setText("21");
    addpage_week22btn->setText("22");
    addpage_week23btn->setText("23");
    addpage_week24btn->setText("24");
    addpage_week25btn->setText("25");

    //13节课程复选按钮
    addpage_course1btn = new QCheckBox(addpage);
    addpage_course2btn = new QCheckBox(addpage);
    addpage_course3btn = new QCheckBox(addpage);
    addpage_course4btn = new QCheckBox(addpage);
    addpage_course5btn = new QCheckBox(addpage);
    addpage_course6btn = new QCheckBox(addpage);
    addpage_course7btn = new QCheckBox(addpage);
    addpage_course8btn = new QCheckBox(addpage);
    addpage_course9btn = new QCheckBox(addpage);
    addpage_course10btn = new QCheckBox(addpage);
    addpage_course11btn = new QCheckBox(addpage);
    addpage_course12btn = new QCheckBox(addpage);
    addpage_course13btn = new QCheckBox(addpage);

    coursenumbtns[1] = addpage_course1btn;
    coursenumbtns[2] = addpage_course2btn;
    coursenumbtns[3] = addpage_course3btn;
    coursenumbtns[4] = addpage_course4btn;
    coursenumbtns[5] = addpage_course5btn;
    coursenumbtns[6] = addpage_course6btn;
    coursenumbtns[7] = addpage_course7btn;
    coursenumbtns[8] = addpage_course8btn;
    coursenumbtns[9] = addpage_course9btn;
    coursenumbtns[10] = addpage_course10btn;
    coursenumbtns[11] = addpage_course11btn;
    coursenumbtns[12] = addpage_course12btn;
    coursenumbtns[13] = addpage_course13btn;

    addpage_course1btn->setText("1");
    addpage_course2btn->setText("2");
    addpage_course3btn->setText("3");
    addpage_course4btn->setText("4");
    addpage_course5btn->setText("5");
    addpage_course6btn->setText("6");
    addpage_course7btn->setText("7");
    addpage_course8btn->setText("8");
    addpage_course9btn->setText("9");
    addpage_course10btn->setText("10");
    addpage_course11btn->setText("11");
    addpage_course12btn->setText("12");
    addpage_course13btn->setText("13");


    //7天星期复选按钮
    addpage_day1btn = new QCheckBox(addpage);
    addpage_day2btn = new QCheckBox(addpage);
    addpage_day3btn = new QCheckBox(addpage);
    addpage_day4btn = new QCheckBox(addpage);
    addpage_day5btn = new QCheckBox(addpage);
    addpage_day6btn = new QCheckBox(addpage);
    addpage_day7btn = new QCheckBox(addpage);

    daybtns[1] = addpage_day1btn;
    daybtns[2] = addpage_day2btn;
    daybtns[3] = addpage_day3btn;
    daybtns[4] = addpage_day4btn;
    daybtns[5] = addpage_day5btn;
    daybtns[6] = addpage_day6btn;
    daybtns[7] = addpage_day7btn;

    addpage_day1btn->setText("1");
    addpage_day2btn->setText("2");
    addpage_day3btn->setText("3");
    addpage_day4btn->setText("4");
    addpage_day5btn->setText("5");
    addpage_day6btn->setText("6");
    addpage_day7btn->setText("7");

    //位置布局
    coursenamelabel->move(addpage_x,50);
    teachernamelabel->move(addpage_x,120);
    courselocationlabel->move(addpage_x,190);
    addpage_coursenameedit->move(addpage_x*1.5,50);
    addpage_teachernameedit->move(addpage_x*1.5,120);
    addpage_courselocationedit->move(addpage_x*1.5,190);

    //周数布局
    addpage_weeklabel->move(addpage_x,250);
    for(int i = 1;i<=25;i++){
        weekbtns[i]->setFixedSize(100,100);
        weekbtns[i]->move(addpage_x+checkbox_hmargin*((i-1)%8),280+checkbox_vmargin*((i-1)/8));
    }

    //节数布局
    addpage_coursenumlabel->move(addpage_x,540);
    for(int i = 1;i<=13;i++){
        coursenumbtns[i]->setFixedSize(100,100);
        coursenumbtns[i]->move(addpage_x+checkbox_hmargin*((i-1)%8),580+checkbox_vmargin*((i-1)/8));
    }

    //星期布局
    addpage_daylabel->move(addpage_x,720);
    for(int i =1;i<=7;i++){
        daybtns[i]->setFixedSize(100,100);
        daybtns[i]->move(addpage_x+checkbox_hmargin*((i-1)%8),760+checkbox_vmargin*((i-1)/8));
    }

    //确认按钮布局
    addpage_comfirmbtn->move(addpage_x*1.5,850);
    addpage_comfirmbtn->setText("新增");
    addpage_savebtn->move(addpage_x*1.5,850);
    addpage_savebtn->setText("保存");
    addpage_savebtn->show();

    connect(addpage_comfirmbtn,&QPushButton::clicked,this,&schoolclass::addpage_comfirmbtn_push);
    connect(addpage_savebtn,&QPushButton::clicked,this,&schoolclass::addpage_savebtn_push);



}

void schoolclass::initsettingpage(){
    settingpage_dateedit = new QCalendarWidget(settingpage);
    settingpage_datelabel = new QLabel(settingpage);
    settingpage_comfirmbtn = new QPushButton(settingpage);

    settingpage_datelabel->setText("设置开学起始日期（第一周星期一）：");
    settingpage_datelabel->setStyleSheet("color:#F6B128");
    QFont font1("微软雅黑",20,QFont::Bold);
    settingpage_datelabel->setFont(font1);
    settingpage_datelabel->setMinimumWidth(250);
    settingpage_datelabel->move(50,40);
    settingpage_datelabel->show();
    settingpage_dateedit->move(380,120);
    //按钮
    settingpage_comfirmbtn->setText("确定");
    settingpage_comfirmbtn->setIcon(QIcon(":/image/lifeandlist/confirmbtn.svg"));
    settingpage_comfirmbtn->setIconSize(QSize(50,50));
    settingpage_comfirmbtn->move(500,450);
    settingpage_comfirmbtn->setStyleSheet("QPushButton { border: none; background: transparent; }"
                              "QPushButton:hover { background-color: #f0f0f0; }");
    //信号与槽
    connect(settingpage_comfirmbtn,&QPushButton::clicked,this,&schoolclass::settingpage_comfirmbtn_push);
}

void schoolclass::leftbtn_push(){
    if(currentweekcount>=2){
        currentweekcount--;
        QString weekstring = "第"+QString::number(currentweekcount)+"周";
        weeklabel->setText(weekstring);
        stackedwidget->setCurrentIndex(currentweekcount);
        settableupperleft_visiable();
    }
    else{
        QMessageBox::warning(this,"警告","已经是第一周");
    }
}

void schoolclass::rightbtn_push(){
    if(currentweekcount<=24){
        currentweekcount++;
        QString weekstring = "第"+QString::number(currentweekcount)+"周";
        weeklabel->setText(weekstring);
        stackedwidget->setCurrentIndex(currentweekcount);
        settableupperleft_visiable();
    }
    else{
        QMessageBox::warning(this,"警告","已经是最后一周");
    }
}

void schoolclass::addbtn_push(){
    addpage_comfirmbtn->show();
    addpage_savebtn->hide();
    stackedwidget->setCurrentWidget(addpage);
    settableupperleft_invisiable();
}

void schoolclass::settingbtn_push(){
    stackedwidget->setCurrentWidget(settingpage);
    settableupperleft_invisiable();
}

void schoolclass::closebtn_push(){
    this->close();
}

void schoolclass::initweekpage(QWidget *weekpage){

}


void schoolclass::mouseMoveEvent(QMouseEvent *event){//长按移动
    if(event->buttons() & Qt::LeftButton){//只要按下了左键，按位与
        this->move(event->globalPos()-topleft);
    }
}

void schoolclass::addpage_comfirmbtn_push(){
    QString newcoursename = addpage_coursenameedit->text();
    QString newteachername = addpage_teachernameedit->text();
    QString newcourselocation = addpage_courselocationedit->text();
    QVector<int> selectedweek;
    QVector<int> selectedcoursenumber;
    int selectedday = 0;

    if(newcoursename.isEmpty() || newteachername.isEmpty() || newcourselocation.isEmpty()){
        QMessageBox::warning(this,"警告","请将基本信息填写完整");
    }
    else{
        //周数
        for(int i =1 ;i<=25;i++){
            if(weekbtns[i]->isChecked()){
                selectedweek.push_back(i);
            }
        }
        //节数
        for(int i = 1;i<=13;i++){
            if(coursenumbtns[i]->isChecked()){
                selectedcoursenumber.push_back(i);
            }
        }
        //星期
        for(int i = 1;i<=7;i++){
            if(selectedday==0 && daybtns[i]->isChecked()){
                selectedday = i;
            }
            else if(selectedday != 0 && daybtns[i]->isChecked()){
                QMessageBox::warning(this,"警告","星期只能选一天！");
                return;
            }
        }
        if(selectedday==0 || selectedweek.isEmpty() || selectedcoursenumber.isEmpty()){
            QMessageBox::warning(this,"警告","请将周数、节数、星期选择完整!");
            return;
        }

        //向数据表插入数据
        insert_sql(newcoursename,newteachername,newcourselocation,selectedweek,selectedcoursenumber,selectedday);
    }



}

void schoolclass::insert_sql(QString coursename,QString teachername,QString courselocation,
                             QVector<int> selectedweek,QVector<int> selectedcoursenumber,int selectedday)
{
    QString columns;
    QString values;
    QSqlQuery query(classdb);


    if(!query.exec("SELECT * FROM class")){//查询所有列
        qDebug()<<"添加失败";
        return;
    }
    int id[1000]={0};
    int selectedid = 0;
    while(query.next()){
        id[query.value("courseid").toInt()]++;
    }

    QString sql = "INSERT INTO class ";
    columns+="courseid,coursename,teachername,courseplace";
    values+=":id,:coursename,:teachername,:courseplace";
    for(int i = 1;i<=999;i++){
        if(!id[i]){
            selectedid = i;
            break;
        }
    }

    //周数
    for(auto week : selectedweek){
        columns+=",week"+QString::number(week);
        values+=",1";
    }
    //节数
    for(auto coursenumber:selectedcoursenumber){
        columns+=",coursenumber"+QString::number(coursenumber);
        values+=",1";
    }
    //星期
    switch (selectedday) {
    case 1:
        columns+=",monday";
        values+=",1";
        break;
    case 2:
        columns+=",tuesday";
        values+=",1";
        break;
    case 3:
        columns += ",wednesday";
        values += ",1";
        break;
    case 4:
        columns += ",thursday";
        values += ",1";
        break;
    case 5:
        columns += ",friday";
        values += ",1";
        break;
    case 6:
        columns += ",saturday";
        values += ",1";
        break;
    case 7:
        columns += ",sunday";
        values += ",1";
        break;
    default:
        break;
    }

    sql+="("+columns+") VALUES ("+values+")";
    query.prepare(sql);
    query.bindValue(":id",selectedid);
    query.bindValue(":coursename",coursename);
    query.bindValue(":teachername",teachername);
    query.bindValue(":courseplace",courselocation);
    qDebug()<<"sql语句"<<sql;

    if(judge_courseconflicts(selectedweek,selectedcoursenumber,selectedday)){
        QMessageBox::warning(this,"警告","与已有课程冲突");
        return;
    }

    if(!query.exec()){
        qDebug()<<"插入"<<coursename<<"失败"<<query.lastError();
        QMessageBox::warning(this,"警告","插入失败");
    }
    else{
        qDebug()<<"插入"<<coursename<<"成功";
        QMessageBox::warning(this,"祝贺","插入成功");
        //刷新页面
        initweekpage();
        removeaddpage();
        stackedwidget->setCurrentIndex(currentweekcount);
        settableupperleft_visiable();
    }

}

void schoolclass::update_sql(int editcourseid, QString coursename, QString teachername, QString courselocation,
                             QVector<int> selectedweek, QVector<int> selectedcoursenumber, int selectedday) {
    // 清除原课程信息
    QSqlQuery query1(classdb);
    QString clearQuery = "UPDATE class SET ";
    QString weeksPart;
    QString courseNumbersPart;
    QString daysPart;

    for (int i = 1; i <= 25; ++i) {
        weeksPart += QString("week%1 = 0, ").arg(i);
    }

    for (int i = 1; i <= 13; ++i) {
        courseNumbersPart += QString("coursenumber%1 = 0, ").arg(i);
    }

    daysPart += "monday = 0,tuesday = 0,wednesday = 0,thursday = 0,friday = 0,saturday = 0,sunday = 0";

    clearQuery += weeksPart + courseNumbersPart + daysPart;
    clearQuery += " WHERE courseid = :courseid";
    query1.prepare(clearQuery);
    query1.bindValue(":courseid", editcourseid);

    if (!query1.exec()) {
        qDebug() << "原课程信息清除不成功" << query1.lastError();
    } else {
        qDebug() << "找到原课程信息";
    }

    // 更新新课程信息
    QSqlQuery query2(classdb);
    QString columns;
    QString sql = "UPDATE class SET coursename = :coursename, teachername = :teachername, courseplace = :courselocation ";
    // 周数
    for (auto week : selectedweek) {
        columns += ",week" + QString::number(week) + "=1";
    }
    // 节数
    for (auto coursenumber : selectedcoursenumber) {
        columns += ",coursenumber" + QString::number(coursenumber) + "=1";
    }
    // 星期
    switch (selectedday) {
    case 1:
        columns += ",monday=1";
        break;
    case 2:
        columns += ",tuesday=1";
        break;
    case 3:
        columns += ",wednesday=1";
        break;
    case 4:
        columns += ",thursday=1";
        break;
    case 5:
        columns += ",friday=1";
        break;
    case 6:
        columns += ",saturday=1";
        break;
    case 7:
        columns += ",sunday=1";
        break;
    default:
        break;
    }
    sql += columns + " WHERE courseid = :id";
    query2.prepare(sql);
    query2.bindValue(":coursename", coursename);
    query2.bindValue(":teachername", teachername);
    query2.bindValue(":courselocation", courselocation);
    query2.bindValue(":id", editcourseid);

    qDebug() << "query2" << sql;

    if(judge_courseconflicts(editcourseid,selectedweek,selectedcoursenumber,selectedday)){
        QMessageBox::warning(this,"警告","与已有课程冲突");
        return;
    }

    if (!query2.exec()) {
        qDebug() << "课程更新信息不成功";
    } else {
        qDebug() << "课程更新信息成功";
        QMessageBox::warning(this, "祝贺", "修改成功");
        // 刷新页面
        initweekpage();
        removeaddpage();
        stackedwidget->setCurrentIndex(currentweekcount);
        settableupperleft_visiable();
    }
}




void schoolclass::removeaddpage(){
    addpage_coursenameedit->clear();
    addpage_teachernameedit->clear();
    addpage_courselocationedit->clear();
    for(auto week:weekbtns){
        week->setCheckState(Qt::CheckState::Unchecked);
    }
    for(auto coursenumber : coursenumbtns){
        coursenumber->setCheckState(Qt::CheckState::Unchecked);
    }
    for(auto day : daybtns){
        day->setCheckState(Qt::CheckState::Unchecked);
    }
}

void schoolclass::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        topleft = event->globalPos() - this->pos(); // 计算并存储偏移量
    }
}

void schoolclass::currentweeklabel_click(){
    stackedwidget->setCurrentIndex(currentweekcount);
    settableupperleft_visiable();
}


void schoolclass::editcourse(int id){
    QVector<int> courseweeks;
    QVector<int> coursenumbers;
    int day=0;
    QString coursename;
    QString teachername;
    QString courselocation;

    qDebug()<<"id"<<id;
    //堆叠页面切换
    stackedwidget->setCurrentWidget(addpage);
    settableupperleft_invisiable();

    addpage_comfirmbtn->hide();
    addpage_savebtn->show();
    QSqlQuery query(classdb);
    query.prepare("SELECT * FROM class WHERE courseid = :id");
    query.bindValue(":id",id);
    if(!query.exec()){
        qDebug()<<"查找该课程信息失败";
        return;
    }
    else{
        qDebug()<<"查找该课程信息成功";
        while(query.next()){
            qDebug()<<"进入";
            editcourseid = id;
            coursename = query.value("coursename").toString();
            teachername = query.value("teachername").toString();
            courselocation = query.value("courseplace").toString();
            for(int i = 1;i<=25;i++){
                QString weekstring = "week"+QString::number(i);
                if(query.value(weekstring).toBool()==true){
                    courseweeks.push_back(i);
                }
            }

            for(int i = 1;i<=13;i++){
                QString coursenumberstring = "coursenumber"+QString::number(i);
                if(query.value(coursenumberstring).toBool()==true){
                    coursenumbers.push_back(i);
                }
            }
            for(int i = 1+45;i<=7+45;i++){
                if(query.value(i).toBool()==true){
                    day = i-45+1;
                    break;
                }
            }

        }
    }
    qDebug()<<"test";
    //展示信息
    addpage_coursenameedit->setText(coursename);
    addpage_teachernameedit->setText(teachername);
    addpage_courselocationedit->setText(courselocation);
    for(auto week :courseweeks){
        weekbtns[week]->setCheckState(Qt::Checked);
    }
    for(auto coursenumber : coursenumbers){
        coursenumbtns[coursenumber]->setCheckState(Qt::Checked);
    }
    daybtns[day]->setCheckState(Qt::Checked);


}

void schoolclass::addpage_savebtn_push(){
    QString newcoursename = addpage_coursenameedit->text();
    QString newteachername = addpage_teachernameedit->text();
    QString newcourselocation = addpage_courselocationedit->text();
    QVector<int> selectedweek;
    QVector<int> selectedcoursenumber;
    int selectedday = 0;

    if(newcoursename.isEmpty() || newteachername.isEmpty() || newcourselocation.isEmpty()){
        QMessageBox::warning(this,"警告","请将基本信息填写完整");
    }
    else{
        //周数
        for(int i =1 ;i<=25;i++){
            if(weekbtns[i]->isChecked()){
                selectedweek.push_back(i);
            }
        }
        //节数
        for(int i = 1;i<=13;i++){
            if(coursenumbtns[i]->isChecked()){
                selectedcoursenumber.push_back(i);
            }
        }
        //星期
        for(int i = 1;i<=7;i++){
            if(selectedday==0 && daybtns[i]->isChecked()){
                selectedday = i;
            }
            else if(selectedday != 0 && daybtns[i]->isChecked()){
                QMessageBox::warning(this,"警告","星期只能选一天！");
                return;
            }
        }
        if(selectedday==0 || selectedweek.isEmpty() || selectedcoursenumber.isEmpty()){
            QMessageBox::warning(this,"警告","请将周数、节数、星期选择完整!");
            return;
        }
    }
    update_sql(editcourseid,newcoursename,newteachername,newcourselocation,selectedweek,selectedcoursenumber,selectedday);

}

void schoolclass::deletethiscourse(int id,int week){
    QSqlQuery query(classdb);
    QString sql = "UPDATE class SET ";
    sql+="week"+QString::number(week)+"=0 WHERE courseid = :courseid";
    query.prepare(sql);
    query.bindValue(":courseid",id);
    if(!query.exec()){
        qDebug()<<"删除这个课程错误";
        QMessageBox::warning(this,"警告","删除失败");
    }
    else{
        qDebug()<<"删除这个课程成功";
        QMessageBox::warning(this,"祝贺","删除成功");
        //刷新页面
        initweekpage();
        removeaddpage();
        stackedwidget->setCurrentIndex(currentweekcount);
        settableupperleft_visiable();
    }


}

void schoolclass::deleteallthiscourse(int id){
    QSqlQuery query(classdb);
    query.prepare("DELETE FROM class WHERE courseid = :courseid");
    query.bindValue(":courseid",id);
    if(!query.exec()){
        qDebug()<<"删除这门课程错误";
        QMessageBox::warning(this,"警告","删除失败");
    }
    else{
        qDebug()<<"删除这门课程成功";
        QMessageBox::warning(this,"祝贺","删除成功");
        //刷新页面
        initweekpage();
        removeaddpage();
        stackedwidget->setCurrentIndex(currentweekcount);
        settableupperleft_visiable();
    }
}

bool schoolclass::judge_courseconflicts(QVector<int> selectedweek, QVector<int> selectedcoursenumber, int selectedday) {
    QSqlQuery query(classdb);
    query.prepare("SELECT * FROM class");
    if(!query.exec()){
        qDebug()<<"冲突数据表连接出错";
    }
    else{
        qDebug()<<"冲突数据库连接成功";
        while(query.next()){
            QVector<int> weeks;
            QVector<int> coursenumbers;
            int day = 0;
            for(int i = 4;i<=28;i++){
                weeks.push_back(query.value(i).toInt());
            }
            for(int i = 29;i<=41;i++){
                coursenumbers.push_back(query.value(i).toInt());
            }
            for(int i = 45;i<=51;i++){
                if(query.value(i)==1){
                    day = i-44;
                }
            }
            //检测是否重合
            if(day==selectedday){
                for(int i = 1;i<=25;i++){
                    for(int j = 1;j<=13;j++){
                        if(weeks[i-1]==1 && coursenumbers[j-1]==1 && selectedweek.contains(i) && selectedcoursenumber.contains(j)){
                            qDebug()<<"week"<<i<<"coursenum"<<j;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool schoolclass::judge_courseconflicts(int id,QVector<int> selectedweek, QVector<int> selectedcoursenumber, int selectedday) {
    QSqlQuery query(classdb);
    query.prepare("SELECT * FROM class WHERE courseid!=:courseid");
    query.bindValue(":courseid",id);
    if(!query.exec()){
        qDebug()<<"冲突数据表连接出错";
    }
    else{
        qDebug()<<"冲突数据库连接成功";
        while(query.next()){
            QVector<int> weeks;
            QVector<int> coursenumbers;
            int day = 0;
            for(int i = 4;i<=28;i++){
                weeks.push_back(query.value(i).toInt());
            }
            for(int i = 29;i<=41;i++){
                coursenumbers.push_back(query.value(i).toInt());
            }
            for(int i = 45;i<=51;i++){
                if(query.value(i)==1){
                    day = i-44;
                }
            }

            //检测是否重合
            if(day==selectedday){
                for(int i = 1;i<=25;i++){
                    for(int j = 1;j<=13;j++){
                        if(weeks[i-1]==1 && coursenumbers[j-1]==1 && selectedweek.contains(i) && selectedcoursenumber.contains(j)){
                            qDebug()<<"week"<<i<<"coursenum"<<j;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


void schoolclass::settableupperleft_invisiable(){
    monday->hide();
    tuesday->hide();
    wednesday->hide();
    thursday->hide();
    friday->hide();
    saturday->hide();
    sunday->hide();

    coursenum1->hide();
    coursenum2->hide();
    coursenum3->hide();
    coursenum4->hide();
    coursenum5->hide();
    coursenum6->hide();
    coursenum7->hide();
    coursenum8->hide();
    coursenum9->hide();
    coursenum10->hide();
    coursenum11->hide();
    coursenum12->hide();
    coursenum13->hide();

}
void schoolclass::settableupperleft_visiable(){
    monday->show();
    tuesday->show();
    wednesday->show();
    thursday->show();
    friday->show();
    saturday->show();
    sunday->show();

    coursenum1->show();
    coursenum2->show();
    coursenum3->show();
    coursenum4->show();
    coursenum5->show();
    coursenum6->show();
    coursenum7->show();
    coursenum8->show();
    coursenum9->show();
    coursenum10->show();
    coursenum11->show();
    coursenum12->show();
    coursenum13->show();
}


void schoolclass::settingpage_comfirmbtn_push(){
    QDate selecteddate = settingpage_dateedit->selectedDate();
    if (selecteddate.dayOfWeek() == Qt::Monday) {
        qDebug() << "选中的日期是星期一";
        QSettings cfg("classconfig.ini", QSettings::IniFormat);
        cfg.setValue("selectedDate",selecteddate);
        QMessageBox::warning(this,"祝贺","设置成功，请重启Zora！");
    }
    else {
        QMessageBox::warning(this,"警告","该日期不是星期一！");
        return;
    }
}




