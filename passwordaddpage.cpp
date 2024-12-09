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
