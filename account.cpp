#include "account.h"
#include "ui_account.h"

account::account(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::account)
{
    ui->setupUi(this);  
}

account::~account()
{
    delete ui;
}
