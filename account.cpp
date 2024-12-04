#include "account.h"
#include "ui_account.h"
#include <qdebug.h>
#include <QHeaderView>



account::account(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::account)
{
    ui->setupUi(this);
    parent->setAttribute(Qt::WA_QuitOnClose,false);
    initbutton();
    initpage();
    inittable();
    creat_database_connection();
    show_all_accountdata();
    connect(addpage,&account_addpage::senddata,this,&account::receive_addpage);


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

    connect(removebtn,&QPushButton::clicked,this,&account::show_all_accountdata);
    connect(addbtn,&QPushButton::clicked,this,&account::show_addpage);
    connect(yearbtn,&QPushButton::clicked,this,&account::show_yearpage);
    connect(monthbtn,&QPushButton::clicked,this,&account::show_monthpage);

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
                          "account INTEGER,"
                          "method NVARCHAR,"
                          "description NVARCHAR,"
                          "date DATATIME)");
    if(!ret){
        qDebug() << "创建账单数据表失败"<<query.lastError().text();
    }

    return true;
}

void account::inittable(){
    account_table = new QTableWidget(this);
    account_table->setColumnCount(columncount);

    QStringList horizontalHeader;
    horizontalHeader << "交易编号" << "金额" << "支付方式"<<"描述"<<"支付时间";
    account_table->setHorizontalHeaderLabels(horizontalHeader);
    account_table->setGeometry(0,buttonheight*1.2,900,540);
    account_table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可被用户编辑

}

void account::initpage(){
    addpage = new account_addpage(this);
    yearpage = new account_yearchart(this);
    monthpage = new account_monthchart(this);
    addpage->hide();
    yearpage->hide();
    monthpage->hide();
}

void account::show_all_accountdata(){
    QSqlQuery query;
    if(!query.exec("SELECT * FROM account")){//查询所有列
        qDebug()<<"查询失败";
        return;
    }
    account_table->setRowCount(0);//先删除原有所有行

    int rowcount = 0;
    while(query.next()){
        account_table->insertRow(rowcount);
        for(int i = 0;i<columncount;i++){
            QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
            account_table->setItem(rowcount,i,item);
        }
        ++rowcount;
    }
    account_table->resizeColumnToContents(0);//设置id列最小宽度
    account_table->resizeColumnToContents(4);//设置id列最小宽度
    account_table->show();
}

void account::insert_accountdata(double money,QString method,QString description,QDateTime datetime){
    QSqlQuery query;
    if(!query.exec("SELECT * FROM account")){//查询所有列
        qDebug()<<"添加失败";
        return;
    }
    int id[1000]={0};
    while(query.next()){
        id[query.value("id").toInt()]++;
    }
    query.prepare("INSERT INTO account (id,account,method,description,date) VALUES (:id,:money,:method,:description,:date)");
    for(int i = 0;i<=999;i++){
        if(!id[i]){
            query.bindValue(":id",i);
            break;
        }
    }
    query.bindValue(":money",money);
    query.bindValue(":method",method);
    query.bindValue(":description",description);
    qDebug()<<"insert"<<money<<" "<<method<<" "<<description<<" "<<datetime;
    QString datatimestring = datetime.toString("yyyy-MM-dd HH:mm:ss");
    query.bindValue(":date",datatimestring);
    if (!query.exec()) {
        qDebug() << "插入数据错误 " << query.lastError().text();
    } else {
        qDebug() << "插入数据成功!";
    }

    show_all_accountdata();
}


void account::show_addpage(){
    addpage->setWindowFlag(Qt::Window);
    addpage->setWindowTitle("添加账单");
    yearpage->hide();
    monthpage->hide();
    addpage->show();


}
void account::receive_addpage(double money,QString method,QString description,QDateTime datetime){
    insert_accountdata(money,method,description,datetime);
}

void account::show_yearpage(){

}

void account::show_monthpage(){

}










