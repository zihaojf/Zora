#include "passwordaddpage.h"
#include "ui_passwordaddpage.h"

passwordaddpage::passwordaddpage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::passwordaddpage)
{
    ui->setupUi(this);
}

passwordaddpage::~passwordaddpage()
{
    delete ui;
}

void passwordaddpage::on_pushButton_clicked()
{
    QString webappname = ui->webappedit->text();
    QString username = ui->username_edit->text();
    QString password = ui->passwordedit->text();

    QMessageBox msgBox;
    msgBox.setText("警告");
    msgBox.setWindowFlag(Qt::WindowStaysOnTopHint);
    if(webappname.isEmpty() || username.isEmpty() || password.isEmpty()){
        msgBox.setText("请输入完整的信息！");
        QApplication::setQuitOnLastWindowClosed(false);
        msgBox.exec();
    }
    else {
        if(ui->description_edit->text().isEmpty()){
            QString description = " ";
            QMessageBox::warning(this,"恭喜！","添加成功!");
            emit senddata(webappname,username,password,description);
            ui->webappedit->clear();
            ui->username_edit->clear();
            ui->passwordedit->clear();
            ui->description_edit->clear();
            this->close();
        }
        else{
            QString description = ui->description_edit->text();
            QMessageBox::warning(this,"恭喜！","添加成功!");
            emit senddata(webappname,username,password,description);
            ui->webappedit->clear();
            ui->username_edit->clear();
            ui->passwordedit->clear();
            ui->description_edit->clear();
            this->close();

        }



    }
}

