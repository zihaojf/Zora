#include "cardwidget.h"

CardWidget::CardWidget(QWidget *parent):
    QWidget(parent)
{
    titlelabel = new QLabel(this);
    contentlabel = new QLabel(this);
    timelabel = new QLabel(this);
    titlelabel->setMaximumSize(QSize(300,40));
    contentlabel->setFixedSize(QSize(300,140));
    contentlabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    timelabel->setMaximumSize(QSize(300,20));
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titlelabel);
    layout->addWidget(contentlabel);
    layout->addWidget(timelabel);
    layout->setContentsMargins(10, 10, 10, 10); // 设置布局的边距
    layout->setSpacing(0); // 设置布局中组件的间距为0

    // 设置标签的样式，确保标签背景也是白色
    titlelabel->setStyleSheet(
        "font-size: 18pt; "
        "font-weight: bold; "
        "background-color: #F9F9FB; "
        "border-radius: 20px;"
        );

    contentlabel->setStyleSheet(
        "font-size: 14pt; "
        "background-color: #F9F9FB; "
        "border-radius: 20px;"
        );

    timelabel->setStyleSheet(
        "font-size: 10pt; "
        "color: grey; "
        "background-color: #F9F9FB;"
        );

    contentlabel->setWordWrap(true);

}

void CardWidget::settitle(const QString &title){
    titlelabel->setText(title);
}

void CardWidget::setcontent(const QString &content){
    contentlabel->setText(content);
}

void CardWidget::settime(const QString &time){
    timelabel->setText(time);
}

void CardWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor("#F9F9FB")));
    QRect rect = this->rect();
    int roundRadius = 20;
    painter.drawRoundedRect(rect, roundRadius, roundRadius);

}

void CardWidget::setid(int id){
    widgetid = id;
}

int CardWidget::getid(){
    return widgetid;
}






