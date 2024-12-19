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
    initpage();
    show_alltable();
    connect(passwordaddpage_window,&passwordaddpage::senddata,this,&password::receive_data);//增加按钮槽
}

password::~password()
{
    delete ui;
}

bool password::creat_database_connection()
{
    dbpassword = QSqlDatabase::addDatabase("QSQLITE","passwordconnection");
    dbpassword.setDatabaseName("password.db");
    if(!dbpassword.open()){
        qDebug() << "链接密码记录数据库失败";
        return false;
    }

    QSqlQuery query(dbpassword);
    bool ret = query.exec("CREATE TABLE IF NOT EXISTS password"
                          "(id INTEGER,"
                          "webappname NVARCHAR,"
                          "username NVARCHAR,"
                          "password NVARCHAR,"
                          "description NVARCHAR)");
    if(!ret){
        qDebug() << "数据表失败"<<query.lastError().text();
    }
    else qDebug()<<"密码数据库连接成功";

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
    passwordaddpage_window = new passwordaddpage(this);
    passwordaddpage_window->hide();
    pwdsetting_window = new passwordsettings(this);
    pwdsetting_window->hide();
}

void password::searchbtn_push(){
    QString text = ui->searchedit->text();
    if(text.trimmed().isEmpty()){
        QMessageBox::warning(this,"警告","请输入查询数据！");
    }
    else{
        show_alltable();
        QSqlQuery query(dbpassword);
        query.prepare("SELECT * FROM password WHERE"
                      " (id LIKE :idvalue OR webappname LIKE :webappname OR username LIKE :username OR password LIKE :password OR description LIKE :description)");
        query.bindValue(":idvalue", text.toInt());
        query.bindValue(":webappname", "%" + text + "%");
        query.bindValue(":username", "%" + text + "%");
        query.bindValue(":password", "%" + text + "%");
        query.bindValue(":description", "%" + text + "%");

        if(!query.exec()){
            qDebug()<<"查询失败"<<query.lastError();
            QMessageBox::warning(this,"警告","未查询到数据！");
            ui->searchedit->clear();
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
        qDebug()<<"设定窗口";
        passwordaddpage_window->setWindowFlag(Qt::Window);
        passwordaddpage_window->setWindowTitle("添加密码");
        passwordaddpage_window->setFixedSize(500,400);
        passwordaddpage_window->show();
}

void password::setbtn_push(){

}

void password::show_alltable(){
    QSqlQuery query(dbpassword);
    if(!query.exec("SELECT * FROM password")){//查询所有列
        qDebug()<<"查询失败"<<query.lastError();
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
    connect(deleteaction, &QAction::triggered, this, [this, pos]() {
        delete_password(pos);
    });
    menu.exec(ui->pwtable->mapToGlobal(pos));

}

void password::delete_password(const QPoint &pos){
    QModelIndex index = ui->pwtable->indexAt(pos);
    if(index.isValid()){
        int col = index.column();
        int row = index.row();
        qDebug()<<row<<" "<<col;

        QTableWidgetItem *number = ui->pwtable->item(row,0);
        if(number){
            int id = number->text().toInt();

            QSqlQuery query;
            if(!query.exec("SELECT * FROM password")){//查询所有列
                qDebug()<<"查找数据库失败！";
                return;
            }
            query.prepare("DELETE FROM password WHERE id=:value");
            query.bindValue(":value",id);
            if(!query.exec()){
                qDebug()<<"删除失败";
                QMessageBox::warning(this,"警告","删除失败！");
            }
            else{
                qDebug()<<"删除成功!";
                QMessageBox::warning(this,"祝贺","删除成功！");
            }

            show_alltable();
        }


    }

}

void password::receive_data(QString webappname,QString username,QString password,QString description){
    insertdata(webappname,username,password,description);
}

void password::insertdata(QString webappname,QString username,QString password,QString description){
    QSqlQuery query(dbpassword);
    if(!query.exec("SELECT * FROM password")){//查询所有列
        qDebug()<<"添加失败"<<query.lastError();
        return;
    }
    int id[1000]={0};
    while(query.next()){
        id[query.value("id").toInt()]++;
    }
    query.prepare("INSERT INTO password (id,webappname,username,password,description) VALUES (:id,:webappname,:username,:password,:description)");
    for(int i = 1;i<=999;i++){
        if(!id[i]){
            query.bindValue(":id",i);
            break;
        }
    }
    query.bindValue(":webappname",webappname);
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.bindValue(":description",description);

    qDebug()<<"insert"<<id<<" "<<webappname<<" "<<username<<" "<<password<<description;
    if (!query.exec()) {
        qDebug() << "插入数据错误 " << query.lastError().text();
    } else {
        qDebug() << "插入数据成功!";
    }

    show_alltable();
}

void password::on_setbtn_clicked()
{
    qDebug()<<"打开设置窗口";
    pwdsetting_window->setWindowFlag(Qt::Window);
    pwdsetting_window->setWindowTitle("添加密码");
    pwdsetting_window->setFixedSize(650,480);
    pwdsetting_window->show();
}


void password::on_pushButton_clicked()
{
    show_alltable();
}

