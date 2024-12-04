#include "account_monthchart.h"
#include "ui_account_monthchart.h"

account_monthchart::account_monthchart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::account_monthchart)
{
    ui->setupUi(this);
}

account_monthchart::~account_monthchart()
{
    delete ui;
}
