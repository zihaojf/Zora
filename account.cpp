#include "account.h"
#include "ui_account.h"
#include <qdebug.h>
#include <QHeaderView>



account::account(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::account)
{
    ui->setupUi(this);
    parent->setAttribute(Qt::WA_QuitOnClose,false);//设定父窗口不关闭
    initbutton();//初始化按钮
    initpage();//初始化页面
    inittable();//初始化表格

    creat_database_connection();//连接数据库
    show_all_accountdata();//默认显示所有账单数据
    connect(addpage,&account_addpage::senddata,this,&account::receive_addpage);//增加按钮槽
    setstylesheet();

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

    //暂时不支持年、月总览功能
    yearbtn->hide();
    monthbtn->hide();

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
    connect(searchbtn,&QPushButton::clicked,this,&account::searchbtn_push);

}

bool account::creat_database_connection(){
    accountdb = QSqlDatabase::addDatabase("QSQLITE","accountconnection");
    accountdb.setDatabaseName("account.db");
    if(!accountdb.open()){
        qDebug() << "链接账单数据库失败";
        return false;
    }

    QSqlQuery query(accountdb);
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
    account_table->setContextMenuPolicy(Qt::CustomContextMenu);//设置自定义右键菜单
    connect(account_table, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));//右键槽函数
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
    QSqlQuery query(accountdb);
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
    QSqlQuery query(accountdb);
    if(!query.exec("SELECT * FROM account")){//查询所有列
        qDebug()<<"添加失败";
        return;
    }
    int id[1000]={0};
    while(query.next()){
        id[query.value("id").toInt()]++;
    }
    query.prepare("INSERT INTO account (id,account,method,description,date) VALUES (:id,:money,:method,:description,:date)");
    for(int i = 1;i<=999;i++){
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

void account::searchbtn_push(){
    QString text = searchline_edit->text();
    if(text.trimmed().isEmpty()){
        QMessageBox::warning(this,"警告","请输入查询数据！");
    }
    else{
        show_all_accountdata();
        QSqlQuery query(accountdb);
        query.prepare("SELECT * FROM account WHERE"
                      " (id LIKE :idvalue OR account LIKE :value OR method LIKE :value OR description LIKE :value)");
        query.bindValue(":idvalue", text.toInt());
        qDebug()<<text.toInt();
        query.bindValue(":value", "%" + text + "%");

        if(!query.exec()){
            qDebug()<<"查询失败";
            QMessageBox::warning(this,"警告","未查询到数据！");
        }
        else{
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
            searchline_edit->clear();
        }
    }
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

void account::showContextMenu(const QPoint &pos) {
    QMenu menu;
    QAction *deleteaction = menu.addAction("删除账单");
    connect(deleteaction,&QAction::triggered,this,&account::delete_accountdata);
    menu.exec(account_table->mapToGlobal(pos));

}

void account::delete_accountdata(){
    int id = QInputDialog::getInt(this,"删除账单","请输入您要删除账单的编号：");
    QSqlQuery query(accountdb);
    if(!query.exec("SELECT * FROM account")){//查询所有列
        qDebug()<<"查找数据库失败！";
        return;
    }
    query.prepare("DELETE FROM account WHERE id=:value");
    query.bindValue(":value",id);
    if(!query.exec()){
        qDebug()<<"删除失败";
        QMessageBox::warning(this,"警告","删除失败！");
    }
    else{
        qDebug()<<"删除成功!";
        QMessageBox::warning(this,"祝贺","删除成功！");
    }

    show_all_accountdata();

}

void account::setstylesheet() {
    this->setStyleSheet(R"(
        /* 设置窗口背景色 */
        account {
            background-color: #f0f0f0; /* 淡灰色背景 */
        }

        /* 设置按钮样式 */
        QPushButton {
            background-color: ##FFD822; /* 黄色背景 */
            border: 1px solid #ccc; /* 边框 */
            border-radius: 5px; /* 圆角 */
            padding: 5px 10px; /* 内边距 */
            font-size: 14px; /* 字体大小 */
        }

        QPushButton:hover {
            background-color: #eec900; /* 悬停时颜色加深 */
        }

        QPushButton:pressed {
            background-color: #d4a000; /* 按下时颜色更深 */
        }

        /* 设置LineEdit样式 */
        QLineEdit {
            border: 1px solid #ccc;
            border-radius: 5px;
            padding: 3px 5px;
            font-size: 14px;
        }

        QLineEdit:focus {
            border: 1px solid #ffd700; /* 聚焦时边框颜色 */
        }

        /* 设置表格样式 */
        QTableWidget {
            border: none;
            background-color: #ffffff; /* 表格背景色 */
            alternate-background-color: #f9f9f9; /* 交替行背景色 */
        }

        QTableWidget::item:selected {
            background-color: #c7e8f2; /* 选中项背景色 */
        }

        QHeaderView::section {
            background-color: #e7e7e7; /* 表头背景色 */
            padding: 4px;
            border: 1px solid #ccc;
            font-size: 14px;
        }

        /* 设置菜单样式 */
        QMenu {
            background-color: #ffffff;
            border: 1px solid #ccc;
        }

        QMenu::item {
            padding: 5px 20px;
            border: 1px solid transparent; /* 默认无边框 */
        }

        QMenu::item:selected {
            color: #ffd700;
            background-color: #c7e8f2;
        }

        /* 设置输入对话框样式 */
        QInputDialog {
            background-color: #f0f0f0;
        }
    )");
}








