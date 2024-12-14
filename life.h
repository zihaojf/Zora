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
#include <QLineEdit>
#include "cardwidget.h"
#include <QScrollArea>
#include <qdebug.h>
#include <QDateTime>
#include <QTextEdit>
#include <QMessageBox>

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
    void initnotedetailpage();
    void initnoteaddpage();
    void mouseMoveEvent(QMouseEvent *event);
    void closebtn_push();
    void notebtn_push();
    void listbtn_push();
    void settingbtn_push();
    void noteaddbtn_push();
    void listaddbtn_push();
    void initcardwidget();
    void creatnotecardwidget(int id,QString title,QString content,QString updatedtime,int rowcount);
    void notecard_push(int id);
    void notedetail(int id);
    void updatenotecard();
    void notesavebtn_push();
    void notedeletebtn_push();
    void noteaddpage_savebtn_push();


    //数据库
    bool creat_notedatabase_connection();
    bool creat_listdatabase_connection();

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
    QPushButton *notesavebtn;
    QPushButton *notereturnbtn;
    QPushButton *notedeletebtn;
    QPushButton *noteaddpage_savebtn;
    QPushButton *noteaddpage_returnbtn;
    QLineEdit *noteaddpage_titleEdit;
    QTextEdit *noteaddpage_contentedit;
    QLineEdit *titleEdit;
    QLabel *timelabel;
    QTextEdit *contentedit;

    int notecolumncount = 5;
    QList<CardWidget *> notecardwidgets;
    QScrollArea *notescrollArea;
    QScrollArea *listscrollArea;
    int notepageminheight;
    QLabel *notestatelabel;
    QLabel *liststatelabel;
    QLabel *settingstatelabel;
    QLabel *notedetail_id_label;

};

#endif // LIFE_H
