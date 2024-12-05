#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>
#include <QBitmap>
#include <QPainter>
#include<QWheelEvent>
#include<QPushButton>
#include<QButtonGroup>
#include <QMediaPlayer>
#include <QListView>
#include <QStandardItemModel>

namespace Ui {
class music;
}

class music : public QWidget
{
    Q_OBJECT

public:
    explicit music(QWidget *parent = nullptr);
    ~music();

    void initbutton();

private:
    Ui::music *ui;
    //窗口大小：1200x800
    QPushButton *playbtn;
    QPushButton *nextsongbtn;
    QPushButton *presongbtn;
    QPushButton *fileselectbtn;
    QPushButton *playmode;
    bool playstate;
    int playmodestate;
    QListView *musiclistview;
    QStandardItemModel *musiclistmodel;
};

#endif // MUSIC_H
