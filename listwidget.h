#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPainter>
#include <QFont>
#include <QMenu>
#include <QContextMenuEvent>

class listwidget:public QWidget
{
    Q_OBJECT
public:
    explicit listwidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void setid(int id);
    void settitle(QString title);
    QString gettitle();
    int getid();

    void setlabelchecked();
    void setlabelunchecked();


    QHBoxLayout *layout;
    QCheckBox *checkbox;
    QLabel *label;
    int listwidget_id;
protected:
    void checkboxstatechanged();
    void contextMenuEvent(QContextMenuEvent *event) override
    {
        QMenu menu(this);
        QAction *deleteaction = new QAction("删除待办", this);
        menu.addAction(deleteaction);
        connect(deleteaction, &QAction::triggered, this, &listwidget::ondeleteoption);
        menu.exec(event->globalPos());
    }

signals:
    void getcheckboxstatement(int state,int id);
    void getdeleteaction(int id);

private slots:
    void ondeleteoption(){
        emit getdeleteaction(listwidget_id);
    }


};

#endif // LISTWIDGET_H
