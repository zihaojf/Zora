#ifndef SCHOOLCLASS_H
#define SCHOOLCLASS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QStackedWidget>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QCalendar>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QMessageBox>
#include <QVector>
#include <QString>
#include <QCalendarWidget>
#include <QSettings>
#include "coursecard.h"
#include "coursetabelwidget.h"

namespace Ui {
class schoolclass;
}

class schoolclass : public QWidget
{
    Q_OBJECT

public:
    explicit schoolclass(QWidget *parent = nullptr);
    ~schoolclass();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    bool create_database_connection();
    void initpage();
    void initupperpage();
    void initcoursetabel_upper_left();
    void initweekpage();
    void initaddpage();
    void initsettingpage();
    void inittable();
    void initdatecount();
    void currentweeklabel_click();
    void leftbtn_push();
    void rightbtn_push();
    void closebtn_push();
    void addbtn_push();
    void settingbtn_push();
    void settingpage_comfirmbtn_push();
    void settableupperleft_invisiable();
    void settableupperleft_visiable();
    bool judge_courseconflicts(QVector<int>, QVector<int>, int);
    bool judge_courseconflicts(int,QVector<int>, QVector<int>, int);
    void initweekpage(QWidget *weekpage);
    void insert_sql(QString,QString,QString,QVector<int>,QVector<int>,int);
    void update_sql(int,QString,QString,QString,QVector<int>,QVector<int>,int);
    void addpage_comfirmbtn_push();
    void addpage_savebtn_push();
    void removeaddpage();
    void editcourse(int id);//编辑页面
    void deletethiscourse(int id,int week);//删除本周这门课
    void deleteallthiscourse(int id);//删除所有这门课

private:
    Ui::schoolclass *ui;
    QSqlDatabase classdb;
    QPushButton *leftbtn;
    QPushButton *rightbtn;
    QPushButton *addbtn;
    QPushButton *settingbtn;
    QPushButton *closebtn;
    QLabel *weeklabel;
    QLabel *currentweeklabel;
    QPoint topleft;

    //日期
    QDate initdate;
    int initweeknumber;
    QDate currentdate;
    int currentweeknumber;//当前时间所在周数number
    int daydifference = 0;//当前日期与开学日期差

    const int window_width = 1600;
    const int window_height = 1200;

    //页面
    QStackedWidget *stackedwidget;
    QWidget *addpage;
    QWidget *settingpage;
    QWidget *coursedetailpage;
    QWidget *week1page;
    QWidget *week2page;
    QWidget *week3page;
    QWidget *week4page;
    QWidget *week5page;
    QWidget *week6page;
    QWidget *week7page;
    QWidget *week8page;
    QWidget *week9page;
    QWidget *week10page;
    QWidget *week11page;
    QWidget *week12page;
    QWidget *week13page;
    QWidget *week14page;
    QWidget *week15page;
    QWidget *week16page;
    QWidget *week17page;
    QWidget *week18page;
    QWidget *week19page;
    QWidget *week20page;
    QWidget *week21page;
    QWidget *week22page;
    QWidget *week23page;
    QWidget *week24page;
    QWidget *week25page;
    QVector<QWidget *> weekpages;

    //课程表表头
    //上部
    QLabel *monday;
    QLabel *tuesday;
    QLabel *wednesday;
    QLabel *thursday;
    QLabel *friday;
    QLabel *saturday;
    QLabel *sunday;
    //左侧
    QLabel *coursenum1;
    QLabel *coursenum2;
    QLabel *coursenum3;
    QLabel *coursenum4;
    QLabel *coursenum5;
    QLabel *coursenum6;
    QLabel *coursenum7;
    QLabel *coursenum8;
    QLabel *coursenum9;
    QLabel *coursenum10;
    QLabel *coursenum11;
    QLabel *coursenum12;
    QLabel *coursenum13;

    int uppertabel_hinterval = 200;
    int uppertabel_x = 200;
    int uppertabel_y = 95;
    int lefttable_vinterval = 80;
    int lefttable_x = 40;
    int lefttable_y = 160;

    //每个页面对应的课程表
    QMap<int,coursetabelwidget *> tables;
    coursetabelwidget *table1;
    coursetabelwidget *table2;
    coursetabelwidget *table3;
    coursetabelwidget *table4;
    coursetabelwidget *table5;
    coursetabelwidget *table6;
    coursetabelwidget *table7;
    coursetabelwidget *table8;
    coursetabelwidget *table9;
    coursetabelwidget *table10;
    coursetabelwidget *table11;
    coursetabelwidget *table12;
    coursetabelwidget *table13;
    coursetabelwidget *table14;
    coursetabelwidget *table15;
    coursetabelwidget *table16;
    coursetabelwidget *table17;
    coursetabelwidget *table18;
    coursetabelwidget *table19;
    coursetabelwidget *table20;
    coursetabelwidget *table21;
    coursetabelwidget *table22;
    coursetabelwidget *table23;
    coursetabelwidget *table24;
    coursetabelwidget *table25;

    //添加页面
    QMap<int,QCheckBox*> weekbtns;
    QMap<int,QCheckBox*> coursenumbtns;
    QMap<int,QCheckBox*> daybtns;
    QLabel *coursenamelabel;
    QLabel *teachernamelabel;
    QLabel *courselocationlabel;
    QLabel *addpage_weeklabel;
    QLabel *addpage_coursenumlabel;
    QLabel *addpage_daylabel;
    QLineEdit *addpage_coursenameedit;
    QLineEdit *addpage_teachernameedit;
    QLineEdit *addpage_courselocationedit;

    //25周复选按钮
    QCheckBox *addpage_week1btn;
    QCheckBox *addpage_week2btn;
    QCheckBox *addpage_week3btn;
    QCheckBox *addpage_week4btn;
    QCheckBox *addpage_week5btn;
    QCheckBox *addpage_week6btn;
    QCheckBox *addpage_week7btn;
    QCheckBox *addpage_week8btn;
    QCheckBox *addpage_week9btn;
    QCheckBox *addpage_week10btn;
    QCheckBox *addpage_week11btn;
    QCheckBox *addpage_week12btn;
    QCheckBox *addpage_week13btn;
    QCheckBox *addpage_week14btn;
    QCheckBox *addpage_week15btn;
    QCheckBox *addpage_week16btn;
    QCheckBox *addpage_week17btn;
    QCheckBox *addpage_week18btn;
    QCheckBox *addpage_week19btn;
    QCheckBox *addpage_week20btn;
    QCheckBox *addpage_week21btn;
    QCheckBox *addpage_week22btn;
    QCheckBox *addpage_week23btn;
    QCheckBox *addpage_week24btn;
    QCheckBox *addpage_week25btn;

    //确认按钮
    QPushButton *addpage_comfirmbtn;
    //编辑保存按钮
    QPushButton *addpage_savebtn;

    //13节课复选按钮
    QCheckBox *addpage_course1btn;
    QCheckBox *addpage_course2btn;
    QCheckBox *addpage_course3btn;
    QCheckBox *addpage_course4btn;
    QCheckBox *addpage_course5btn;
    QCheckBox *addpage_course6btn;
    QCheckBox *addpage_course7btn;
    QCheckBox *addpage_course8btn;
    QCheckBox *addpage_course9btn;
    QCheckBox *addpage_course10btn;
    QCheckBox *addpage_course11btn;
    QCheckBox *addpage_course12btn;
    QCheckBox *addpage_course13btn;

    //7天复选按钮
    QCheckBox *addpage_day1btn;
    QCheckBox *addpage_day2btn;
    QCheckBox *addpage_day3btn;
    QCheckBox *addpage_day4btn;
    QCheckBox *addpage_day5btn;
    QCheckBox *addpage_day6btn;
    QCheckBox *addpage_day7btn;

    //设置页面
    QCalendarWidget *settingpage_dateedit;
    QLabel *settingpage_datelabel;
    QPushButton *settingpage_comfirmbtn;

    int checkboxwidth;
    int checkboxheight;
    int checkbox_hmargin = 60;
    int checkbox_vmargin = 50;
    int addpage_x = 350;

    int editcourseid = 0;


    //测试
    int currentweekcount=1;//周数label显示计数器

};

#endif // SCHOOLCLASS_H
