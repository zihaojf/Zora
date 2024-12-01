#include "account.h"
#include "ui_account.h"
#include <qdebug.h>



account::account(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::account)
{
    ui->setupUi(this);
    // 创建 SQLite 数据库连接
    QSqlDatabase account_database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        account_database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        account_database = QSqlDatabase::addDatabase("QSQLITE");
        account_database.setDatabaseName("MyDataBase.db");
    }

    //调试
    if (!account_database.open())
    {
        qDebug() << "Error: Failed to connect database." << account_database.lastError();
    }
    else
    {

    }
    //创建数据库中表格
    //设置id初始大小
    temp_account_id=1;

    QString create_sql = "create table account (id int primary key,money int, text varchar(30), day DATE)";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}
account::~account()
{
    delete ui;
}


void account::renewaccount_database(){
    //插入新数据
    QString insert_sql = "insert into account values (?, ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(temp_account_id+1);
    sql_query.addBindValue(temp_account_money);
    sql_query.addBindValue(temp_account_text);
    sql_query.addBindValue(temp_account_day);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted Wang!";
    }
    if(!sql_query.exec("INSERT INTO account VALUES(3, \"Li\", 23)"))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted Li!";
    }

}

void account::setaccount_tableWidget(){
    // 创建 QTableWidget
    account_tableWidget=new QTableWidget(this);

    //查找数据库中的表
    QString tableName = "softwareproject";
    QSqlQuery query;
    query.exec(QString("select * from %1").arg(tableName));

    //设置tablewidget的表头项
    account_tableWidget->setHorizontalHeaderLabels({"编号", "金额", "内容", "日期"});
    int row = 0;
    while(query.next())
    {
        account_tableWidget->setRowCount(row+1);
        for(int column = 0; column < query.record().count(); column++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());
            account_tableWidget->setItem(row,column,item);
        }
        row++;
    }

}


void account::on_account_addButton_clicked()
{
    //获取文本框数据
    QString account_program1 = ui->account_moneylineEdit->text();
    QString account_program2 = ui->account_textlineEdit->text();
    QString account_program3 = ui->account_datelineEdit->text();
    temp_account_money=account_program1;
    temp_account_text=account_program2;
    //date那个不晓得怎么办
}



