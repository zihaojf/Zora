#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>
#include <QBitmap>
#include <QPainter>
#include<QWheelEvent>
#include<QPushButton>
#include<QButtonGroup>
#include <QMediaPlayer>

namespace Ui {
class music;
}

class music : public QWidget
{
    Q_OBJECT

public:
    explicit music(QWidget *parent = nullptr);
    ~music();

private:
    Ui::music *ui;
};

#endif // MUSIC_H
