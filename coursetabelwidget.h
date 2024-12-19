#ifndef COURSETABELWIDGET_H
#define COURSETABELWIDGET_H

#include <QWidget>
#include <QMap>
#include <QDebug>
#include "coursecard.h"

class coursetabelwidget : public QWidget
{
    Q_OBJECT
public:
    explicit coursetabelwidget(QWidget *parent = nullptr);
    QMap<int,coursecard *> coursecards;
    void newcourses();
    void initcourseslocation();
    void setcoursecard(int number,int id,int week,QString firstlabel,QString secondlabel);

    // 星期一
    coursecard *coursemonday1;
    coursecard *coursemonday2;
    coursecard *coursemonday3;
    coursecard *coursemonday4;
    coursecard *coursemonday5;
    coursecard *coursemonday6;
    coursecard *coursemonday7;
    coursecard *coursemonday8;
    coursecard *coursemonday9;
    coursecard *coursemonday10;
    coursecard *coursemonday11;
    coursecard *coursemonday12;
    coursecard *coursemonday13;

    // 星期二
    coursecard *coursetuesday1;
    coursecard *coursetuesday2;
    coursecard *coursetuesday3;
    coursecard *coursetuesday4;
    coursecard *coursetuesday5;
    coursecard *coursetuesday6;
    coursecard *coursetuesday7;
    coursecard *coursetuesday8;
    coursecard *coursetuesday9;
    coursecard *coursetuesday10;
    coursecard *coursetuesday11;
    coursecard *coursetuesday12;
    coursecard *coursetuesday13;

    // 星期三
    coursecard *coursewednesday1;
    coursecard *coursewednesday2;
    coursecard *coursewednesday3;
    coursecard *coursewednesday4;
    coursecard *coursewednesday5;
    coursecard *coursewednesday6;
    coursecard *coursewednesday7;
    coursecard *coursewednesday8;
    coursecard *coursewednesday9;
    coursecard *coursewednesday10;
    coursecard *coursewednesday11;
    coursecard *coursewednesday12;
    coursecard *coursewednesday13;

    // 星期四
    coursecard *coursethursday1;
    coursecard *coursethursday2;
    coursecard *coursethursday3;
    coursecard *coursethursday4;
    coursecard *coursethursday5;
    coursecard *coursethursday6;
    coursecard *coursethursday7;
    coursecard *coursethursday8;
    coursecard *coursethursday9;
    coursecard *coursethursday10;
    coursecard *coursethursday11;
    coursecard *coursethursday12;
    coursecard *coursethursday13;

    // 星期五
    coursecard *coursefriday1;
    coursecard *coursefriday2;
    coursecard *coursefriday3;
    coursecard *coursefriday4;
    coursecard *coursefriday5;
    coursecard *coursefriday6;
    coursecard *coursefriday7;
    coursecard *coursefriday8;
    coursecard *coursefriday9;
    coursecard *coursefriday10;
    coursecard *coursefriday11;
    coursecard *coursefriday12;
    coursecard *coursefriday13;

    // 星期六
    coursecard *coursesaturday1;
    coursecard *coursesaturday2;
    coursecard *coursesaturday3;
    coursecard *coursesaturday4;
    coursecard *coursesaturday5;
    coursecard *coursesaturday6;
    coursecard *coursesaturday7;
    coursecard *coursesaturday8;
    coursecard *coursesaturday9;
    coursecard *coursesaturday10;
    coursecard *coursesaturday11;
    coursecard *coursesaturday12;
    coursecard *coursesaturday13;

    // 星期天
    coursecard *coursesunday1;
    coursecard *coursesunday2;
    coursecard *coursesunday3;
    coursecard *coursesunday4;
    coursecard *coursesunday5;
    coursecard *coursesunday6;
    coursecard *coursesunday7;
    coursecard *coursesunday8;
    coursecard *coursesunday9;
    coursecard *coursesunday10;
    coursecard *coursesunday11;
    coursecard *coursesunday12;
    coursecard *coursesunday13;

    int onedaycourse = 13;
    int vinterval = 80;
    int hinterval = 200;

signals:
};

#endif // COURSETABELWIDGET_H
