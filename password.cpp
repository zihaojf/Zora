#include "password.h"
#include "ui_password.h"

password::password(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::password)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose, false);//设定该窗口关闭之后不会让程序关闭
    parent->setAttribute(Qt::WA_QuitOnClose,false);//设定父窗口不关闭
    creat_database_connection();
    initbutton();
    inittable();
    show_alltable();

}

password::~password()
{
    delete ui;
}

bool password::creat_database_connection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("password.db");
    if(!db.open()){
        qDebug() << "链接密码记录数据库失败";
        return false;
    }

    QSqlQuery query;
    bool ret = query.exec("CREATE TABLE IF NOT EXISTS password"
                          "(id INTEGER,"
                          "webappname NVARCHAR,"
                          "username NVARCHAR,"
                          "password NVARCHAR,"
                          "description NVARCHAR)");
    if(!ret){
        qDebug() << "创建账单数据表失败"<<query.lastError().text();
    }

    return true;
}

void password::initbutton(){
    connect(ui->searchbtn,&QPushButton::clicked,this,&password::searchbtn_push);
    connect(ui->addbtn,&QPushButton::clicked,this,&password::addbtn_push);
    connect(ui->setbtn,&QPushButton::clicked,this,&password::setbtn_push);
}

void password::inittable(){
    //ui->pwtable = new QTableWidget(this);
    ui->pwtable->setColumnCount(columncount);
    ui->pwtable->setContextMenuPolicy(Qt::CustomContextMenu);//设置自定义右键菜单
    connect(ui->pwtable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));//右键槽函数
    QStringList horizontalHeader;
    horizontalHeader << "编号" << "网站/app" << "用户名"<<"密码"<<"备注";
    ui->pwtable->setHorizontalHeaderLabels(horizontalHeader);
    ui->pwtable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可被用户编辑
}

void password::initpage(){

}

void password::searchbtn_push(){
    QString text = ui->searchedit->text();
    if(text.trimmed().isEmpty()){
        QMessageBox::warning(this,"警告","请输入查询数据！");
    }
    else{
        show_alltable();
        QSqlQuery query;
        query.prepare("SELECT * FROM password WHERE"
                      " (id LIKE :idvalue OR webappname LIKE :value OR username LIKE :value OR password LIKE :value OR description LIKE :value)");
        query.bindValue(":idvalue", text.toInt());
        qDebug()<<text.toInt();
        query.bindValue(":value", "%" + text + "%");

        if(!query.exec()){
            qDebug()<<"查询失败";
            QMessageBox::warning(this,"警告","未查询到数据！");
        }
        else{
            qDebug()<<"查询成功！";
            ui->pwtable->setRowCount(0);//先删除原有所有行
            int rowcount = 0;
            while(query.next()){
                ui->pwtable->insertRow(rowcount);
                for(int i = 0;i<columncount;i++){
                    QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
                    ui->pwtable->setItem(rowcount,i,item);
                }
                ++rowcount;
            }
            ui->pwtable->resizeColumnToContents(0);//设置id列最小宽度
            ui->pwtable->resizeColumnToContents(4);//设置id列最小宽度
            ui->pwtable->show();
            ui->searchedit->clear();
        }
    }
}

void password::addbtn_push(){

}

void password::setbtn_push(){

}

void password::show_alltable(){
    QSqlQuery query;
    if(!query.exec("SELECT * FROM password")){//查询所有列
        qDebug()<<"查询失败";
        return;
    }
    ui->pwtable->setRowCount(0);//先删除原有所有行

    int rowcount = 0;
    while(query.next()){
        ui->pwtable->insertRow(rowcount);
        for(int i = 0;i<columncount;i++){
            QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
            ui->pwtable->setItem(rowcount,i,item);
        }
        ++rowcount;
    }
    ui->pwtable->resizeColumnToContents(0);//设置id列最小宽度
    ui->pwtable->resizeColumnToContents(4);//设置id列最小宽度
    ui->pwtable->show();

}

void password::showContextMenu(const QPoint &pos) {
    QMenu menu;
    QAction *deleteaction = menu.addAction("删除密码");
    connect(deleteaction,&QAction::triggered,this,&password::delete_password);
    menu.exec(ui->pwtable->mapToGlobal(pos));

}

void password::delete_password(){

}
