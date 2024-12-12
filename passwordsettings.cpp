#include "passwordsettings.h"
#include "ui_passwordsettings.h"

passwordsettings::passwordsettings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::passwordsettings)
{
    ui->setupUi(this);
}

passwordsettings::~passwordsettings()
{
    delete ui;
}



void passwordsettings::on_confirmbtn_clicked()
{
    QString originalpwd = ui->originalpwd->text();
    QString newpwd = ui->newpwd->text();
    QString newpwdagain = ui->newpwdagain->text();

    QMessageBox msgBox;
    msgBox.setText("警告");
    msgBox.setWindowFlag(Qt::WindowStaysOnTopHint);
    if(originalpwd.isEmpty() || newpwd.isEmpty() || newpwdagain.isEmpty()){
        msgBox.setText("请输入完整的信息！");
        QApplication::setQuitOnLastWindowClosed(false);
        msgBox.exec();
    }
    else {
        QSettings cfg("pwconfig.ini", QSettings::IniFormat);
        QString password = cfg.value("password").toString();
        if(password == originalpwd){
            if(newpwd == newpwdagain){
                cfg.setValue("password",newpwd);
                QMessageBox::warning(this,"恭喜！","修改成功!");
                ui->newpwd->clear();
                ui->originalpwd->clear();
                ui->newpwdagain->clear();
                this->close();
            }
            else{
                msgBox.setText("请输入相同的的新密码！");
                QApplication::setQuitOnLastWindowClosed(false);
                msgBox.exec();
            }
        }
        else{
            msgBox.setText("请输入正确的的原密码！");
            QApplication::setQuitOnLastWindowClosed(false);
            msgBox.exec();
        }

    }
}

