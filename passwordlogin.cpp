#include "passwordlogin.h"
#include "ui_passwordlogin.h"

passwordlogin::passwordlogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::passwordlogin)
{
    ui->setupUi(this);
    init();
}

passwordlogin::~passwordlogin()
{
    delete ui;
}

void passwordlogin::loginbtn_push(){
    QString lineEditstring = ui->lineEdit->text();
    QSettings cfg("pwconfig.ini", QSettings::IniFormat);
    password = cfg.value("password").toString();
    if(lineEditstring==password){
        password_window->move(800,600);
        password_window->setWindowFlag(Qt::Window);
        password_window->setWindowTitle("密码记录器");
        password_window->setFixedSize(800,600);
        password_window->show();
        ui->lineEdit->clear();
        QMessageBox::warning(this,"祝贺","登陆成功！");
        this->hide();


    }
    else{
        QMessageBox::warning(this,"警告","密码输入错误");
    }
}


void passwordlogin::init(){
    password_window = new class password(this);
    password_window->hide();
    connect(ui->pushButton,&QPushButton::clicked,this,&passwordlogin::loginbtn_push);
}
