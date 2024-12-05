#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>
#include <QProcess>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QtSql/QsqlRecord>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include "account_addpage.h"
#include "account_monthchart.h"
#include "account_yearchart.h"
#include <QMenu>
#include <QInputDialog>



namespace Ui {
class account;
}

class account : public QWidget
{
    Q_OBJECT

public:
    explicit account(QWidget *parent = nullptr);
    ~account();
    bool creat_database_connection();//设置数据库链接
    void initbutton();
    void initpage();
    void inittable();
    void show_all_accountdata();
    void show_addpage();
    void show_yearpage();
    void show_monthpage();
    void insert_accountdata(double money,QString method,QString description,QDateTime datetime);
    void searchbtn_push();
    void delete_accountdata();

private slots:
    void receive_addpage(double money,QString method,QString description,QDateTime datetime);
    void showContextMenu(const QPoint &pos);


private:
    Ui::account *ui;
    account_addpage *addpage;
    account_monthchart *monthpage;
    account_yearchart *yearpage;
    QSqlDatabase account_db;
    const int columncount=5;//数据库列数
    QSqlDatabase account_database;
    QPushButton *searchbtn;
    QPushButton *addbtn;
    QPushButton *yearbtn;//年总览
    QPushButton *monthbtn;//月总览
    QPushButton *removebtn;//清除搜索条件按钮
    QLineEdit *searchline_edit;//搜索文本框

    QTableWidget *account_table;

    int buttonwidth = 80,buttonheight = 50;
    int line_editwidth = 200,line_editheight = 50;

};

#endif // ACCOUNT_H
