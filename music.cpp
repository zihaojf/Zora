#include "music.h"
#include "ui_music.h"

music::music(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::music)
{
    ui->setupUi(this);
}

music::~music()
{
    delete ui;
}
