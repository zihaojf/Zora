#ifndef COURSECARD_H
#define COURSECARD_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QMenu>
#include <QMouseEvent>

class coursecard : public QWidget
{
    Q_OBJECT
public:
    explicit coursecard(QWidget *parent = nullptr);
    void setcardwidth(int width);
    void setcardheight(int height);
    void setfirstlabel(QString firsttext);
    void setsecondlabel(QString secondtext);
    void setcourseid(int id);
    void setcourseweekid(int week);
    QString getfirstlabel();
    QString getsecondlabel();
    int getcourseid();
    void paintEvent(QPaintEvent *event) override;
    void setfirstlabel_adjustsize();
    void editaction_push();
    void deletethisaction_push();
    void deleteallaction_push();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override
    {
        //右键菜单
        QMenu menu(this);
        editaction = menu.addAction("编辑该课程");
        deletethisaction = menu.addAction("删除本周课程");
        deleteallaction = menu.addAction("删除所有该课程");

        //信号与槽
        connect(editaction,&QAction::triggered,this,&coursecard::editaction_push);
        connect(deletethisaction,&QAction::triggered,this,&coursecard::deletethisaction_push);
        connect(deleteallaction,&QAction::triggered,this,&coursecard::deleteallaction_push);
        menu.exec(event->globalPos());
    }
    void mousePressEvent(QMouseEvent *event) override;


private:
    int cardwidth = 160;
    int cardheight = 40;
    int courseid;
    int courseweekid;
    QLabel *firstlabel;
    QLabel *secondlabel;
    QAction *editaction;
    QAction *deletethisaction;
    QAction *deleteallaction;

signals:
    void geteditaction(int id);
    void getdeletethisaction(int id,int week);
    void getdeleteallaction(int id);

};

#endif // COURSECARD_H
