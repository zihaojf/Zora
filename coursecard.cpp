#include "coursecard.h"

coursecard::coursecard(QWidget *parent)
    : QWidget{parent}
{
    firstlabel = new QLabel(this);
    secondlabel = new QLabel(this);
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(firstlabel);
    layout->addWidget(secondlabel);
    firstlabel->setMinimumWidth(cardwidth);
    firstlabel->setFixedSize(QSize(cardwidth,0.6*cardheight));
    secondlabel->setFixedSize(QSize(cardwidth,0.4*cardheight));
    firstlabel->setStyleSheet(
        "font-size: 11pt; "
        "font-weight: bold; "
        "color:#F6B128;"
        "background-color: #F9F9FB; "
        "border-radius: 20px;"
        );

    secondlabel->setStyleSheet(
        "font-size: 10pt; "
        "background-color: #F9F9FB; "
        "border-radius: 20px;"
        );



}



void coursecard::setcardwidth(int width){
    cardwidth = width;
    firstlabel->setFixedSize(QSize(cardwidth,0.6*cardheight));
    secondlabel->setFixedSize(QSize(cardwidth,0.4*cardheight));
}

void coursecard::setcardheight(int height){
    cardheight = height;
    firstlabel->setFixedSize(QSize(cardwidth,0.6*cardheight));
    secondlabel->setFixedSize(QSize(cardwidth,0.4*cardheight));
}

void coursecard::setfirstlabel(QString firsttext){
    firstlabel->setText(firsttext);
}

void coursecard::setsecondlabel(QString secondtext){
    secondlabel->setText(secondtext);
}

void coursecard::setcourseid(int id){
    courseid = id;
}

void coursecard::setcourseweekid(int week){
    courseweekid = week;
}

QString coursecard::getfirstlabel(){
    return firstlabel->text();
}
QString coursecard::getsecondlabel(){
    return secondlabel->text();
}
int coursecard::getcourseid(){
    return courseid;
}

void coursecard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor("#F9F9FB")));
    QRect rect = this->rect();
    int roundRadius = 20;
    painter.drawRoundedRect(rect, roundRadius, roundRadius);
}


void coursecard::editaction_push(){
    qDebug()<<"编辑";
    emit geteditaction(courseid);
}

void coursecard::deletethisaction_push(){
    qDebug()<<"删除这节课";
    emit getdeletethisaction(courseid,courseweekid);
}

void coursecard::deleteallaction_push(){
    qDebug()<<"删除这门课";
    emit getdeleteallaction(courseid);
}

void coursecard::setfirstlabel_adjustsize(){
    firstlabel->adjustSize();
}

void coursecard::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        editaction_push();
    }
    QWidget::mousePressEvent(event);
}
