#ifndef LIFE_H
#define LIFE_H

#include <QWidget>
#include <QBitmap>
#include <QPainter>
#include<QWheelEvent>
#include<QPushButton>
#include<QButtonGroup>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

namespace Ui {
class life;
}

class life : public QWidget
{
    Q_OBJECT

public:
    explicit life(QWidget *parent = nullptr);
    ~life();
    void initpage();
    void initnotepage();
    void initlistpage();
    void initsettingpage();
    void mouseMoveEvent(QMouseEvent *event);
    void closebtn_push();
    void notebtn_push();
    void listbtn_push();
    void settingbtn_push();
    void noteaddbtn_push();
    void listaddbtn_push();

    //数据库
    bool creat_notedatabase_connection();

private:
    Ui::life *ui;
    QPoint topleft;
    QWidget *notepage;
    QWidget *listpage;
    QWidget *settingpage;
    QWidget *notedetailpage;
    QWidget *listdetailpage;
    QWidget *noteaddpage;
    QWidget *listaddpage;
    QStackedWidget *stackedwidget;

    QPushButton *notebtn;
    QPushButton *listbtn;
    QPushButton *settingbtn;
    QPushButton *closebtn;
    QPushButton *noteaddbtn;
    QPushButton *listaddbtn;

};

#endif // LIFE_H
