#include "account_yearchart.h"
#include "ui_account_yearchart.h"

account_yearchart::account_yearchart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::account_yearchart)
{
    ui->setupUi(this);
}

account_yearchart::~account_yearchart()
{
    delete ui;
}
