#include "account.h"
#include "ui_account.h"
#include <qdebug.h>



account::account(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::account)
{
    ui->setupUi(this);
    initbutton();
    inittable();
    creat_database_connection();


}

account::~account()
{
    delete ui;
}

void account::initbutton(){
    searchbtn = new QPushButton(this);
    searchline_edit = new QLineEdit(this);
    addbtn = new QPushButton(this);
    yearbtn = new QPushButton(this);
    monthbtn = new QPushButton(this);
    removebtn = new QPushButton(this);


    searchbtn->setText(tr("搜索"));
    addbtn->setText(tr("添加"));
    yearbtn->setText(tr("年总览"));
    monthbtn->setText("月总览");
    removebtn->setText("显示所有");

    searchline_edit->setGeometry(10,0,line_editwidth,line_editheight);
    searchbtn->setGeometry(line_editwidth*1.1,0,buttonwidth,buttonheight);
    addbtn->setGeometry((line_editwidth+buttonwidth)*1.2,0,buttonwidth,buttonheight);
    yearbtn->setGeometry((line_editwidth+2*buttonwidth)*1.2,0,buttonwidth,buttonheight);
    monthbtn->setGeometry((line_editwidth+3*buttonwidth)*1.2,0,buttonwidth,buttonheight);
    removebtn->setGeometry((line_editwidth+4*buttonwidth)*1.3,0,buttonwidth*1.5,buttonheight);



}

bool account::creat_database_connection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("account.db");
    if(!db.open()){
        qDebug() << "链接账单数据库失败";
        return false;
    }

    QSqlQuery query;
    bool ret = query.exec("CREATE TABLE IF NOT EXISTS account"
                          "(id INTEGER,"
                          "money INTEGER,"
                          "notes NVARCHAR,"
                          "date DATATIME)");
    if(!ret){
        qDebug() << "创建账单数据表失败"<<query.lastError().text();
    }

    return true;
}

void account::inittable(){
    account_table = new QTableWidget(this);
    account_table->setRowCount(100);
    account_table->setColumnCount(5);

    QStringList horizontalHeader;
    horizontalHeader << "编号" << "金额" << "备注"<<"金额";
    account_table->setHorizontalHeaderLabels(horizontalHeader);
    account_table->setGeometry(0,buttonheight*1.2,900,540);
    account_table->setEditTriggers(QAbstractItemView::NoEditTriggers);


}









