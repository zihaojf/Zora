#include "worksetting.h"
#include "ui_worksetting.h"

worksetting::worksetting(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::worksetting)
{
    ui->setupUi(this);
}

worksetting::~worksetting()
{
    delete ui;
}

void worksetting::on_comfirmbtn_clicked()
{
    int worktime = ui->worktime_m->text().toInt()*60 + ui->worktime_second->text().toInt();
    int relaxtime = ui->relaxtime_m->text().toInt()*60 + ui->relaxtime_second->text().toInt();
    qDebug()<<worktime<<relaxtime;
    emit sendata(worktime,relaxtime);
    QMessageBox::warning(this,"恭喜","设置成功");
    this->close();
}

