#include "account_addpage.h"
#include "ui_account_addpage.h"

account_addpage::account_addpage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::account_addpage)
{
    ui->setupUi(this);


}

account_addpage::~account_addpage()
{
    delete ui;
}

void account_addpage::on_pushButton_clicked()
{
    QString money = ui->moneylineEdit->text();
    QString method = ui->methodlineEdit->text();
    QString description = ui->descriptionlineEdit->text();
    QDateTime datetime = ui->dateTimeEdit->dateTime();

    QMessageBox msgBox;
    msgBox.setText("警告");
    msgBox.setWindowFlag(Qt::WindowStaysOnTopHint);
    if(money.isEmpty() || method.isEmpty() || description.isEmpty()){
        msgBox.setText("请输入完整的信息！");
        QApplication::setQuitOnLastWindowClosed(false);
        msgBox.exec();
    }
    else {
        bool isnumber = false;
        int account = money.toDouble(&isnumber);
        if(!isnumber){
            msgBox.setText("请输入正确的金额！");
            QApplication::setQuitOnLastWindowClosed(false);
            msgBox.exec();
        }
        else{
            QMessageBox::warning(this,"恭喜！","添加成功!");
            emit senddata(account,method,description,datetime);
            this->close();
        }

    }

}


