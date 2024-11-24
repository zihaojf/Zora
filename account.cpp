#include "account.h"
#include "ui_account.h"
#include <QMessageBox>

account::account(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::account)
{
    ui->setupUi(this);

    // 设置表格
    ui->account_tableWidget->setColumnCount(4);
    ui->account_tableWidget->setHorizontalHeaderLabels({"编号", "金额", "内容", "日期"});
    ui->account_tableWidget->horizontalHeader()->setStretchLastSection(true);




}

account::~account()
{
    delete ui;
}


