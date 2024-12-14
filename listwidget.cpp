#include "listwidget.h"

listwidget::listwidget(QWidget *parent):
    QWidget(parent)
{
    layout = new QHBoxLayout(this);
    checkbox = new QCheckBox(this);
    label = new QLabel(this);
    label->setMinimumSize(QSize(1000,38));
    label->setStyleSheet("background-color:#F9F9FB;color:black;");
    layout->addWidget(checkbox);
    layout->addWidget(label);
    label->setText("列表测试");
    connect(checkbox, &QCheckBox::stateChanged, this, &listwidget::checkboxstatechanged);

}

void listwidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor("#F9F9FB")));
    QRect rect = this->rect();
    int roundRadius = 20;
    painter.drawRoundedRect(rect, roundRadius, roundRadius);

}

void listwidget::setid(int id){
    listwidget_id = id;
}

void listwidget::settitle(QString title){
    label->setText(title);
}

QString listwidget::gettitle(){
    return label->text();
}

int listwidget::getid(){
    return listwidget_id;
}


void listwidget::setlabelchecked(){
    label->setStyleSheet("background-color:#F9F9FB;color:grey;");
    QFont font = label->font();
    font.setStrikeOut(true);
    label->setFont(font);
    checkbox->setCheckState(Qt::Checked);
}

void listwidget::setlabelunchecked(){
    label->setStyleSheet("background-color:#F9F9FB;color:black;");
    QFont font = label->font();
    font.setStrikeOut(false);
    label->setFont(font);
}

void listwidget::checkboxstatechanged(){
    if(checkbox->isChecked()){
        setlabelchecked();
    }
    else setlabelunchecked();

    emit getcheckboxstatement(checkbox->isChecked(),listwidget_id);
}


