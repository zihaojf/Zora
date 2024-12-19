#ifndef WORK_H
#define WORK_H

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include <QDatetime>
#include "worksetting.h"

namespace Ui {
class work;
}

class work : public QWidget
{
    Q_OBJECT

public:
    explicit work(QWidget *parent = nullptr);
    ~work();
    void mouseMoveEvent(QMouseEvent *event);//鼠标长按左键移动位置
    void mousePressEvent(QMouseEvent *event);
    void init();
    void startbtn_push();
    void pausebtn_push();
    void removebtn_push();
    void settingbtn_push();


private slots:
    void updatetime();
    void receivedata(int worktime,int relaxtime);
    void setstylesheet();

private:
    Ui::work *ui;
    QPoint topleft;//记录初始的移动左上坐标点
    worksetting *setting_window;
    QPushButton *settingbtn;
    QPushButton *startbtn;
    QPushButton *removebtn;
    QPushButton *pausebtn;
    QLabel *timelabel;
    QLabel *statelabel;
    QTimer *timer;
    int worktimeconst = 1500;
    int relaxtimeconst = 500;
    int worktime;
    int relaxtime;
    bool workrelaxcondition;
};

#endif // WORK_H
