#include "schoolclass.h"
#include "ui_schoolclass.h"

schoolclass::schoolclass(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::schoolclass)
{
    ui->setupUi(this);
}

schoolclass::~schoolclass()
{
    delete ui;
}
