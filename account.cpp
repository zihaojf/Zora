#include "account.h"
#include "ui_account.h"
#include <qdebug.h>



account::account(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::account)
{
    ui->setupUi(this);
    creat_database();

}

account::~account()
{
    delete ui;
}

void account::creat_database(){
    // 创建 SQLite 数据库连接
    QSqlDatabase account_database;
    //检查是否已有数据库，否则重新添加一个数据库
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        account_database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        account_database = QSqlDatabase::addDatabase("QSQLITE");
        account_database.setDatabaseName("account.db");
    }

    //打开数据库
    if (!account_database.open())
    {
        qDebug() << "无法打开数据库！" << account_database.lastError();
    }
    else
    {
        QSqlQuery sql_query(account_database);
        QString create_sql = "create table account (id int primary key,money int, text varchar(30), day DATE)";
        sql_query.prepare(create_sql);
        if(!sql_query.exec())
        {
            qDebug() << "错误: 无法创建数据库." << sql_query.lastError();
        }
        else
        {
            qDebug() << "成功创建数据库!";
        }
    }

}









