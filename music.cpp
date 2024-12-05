#include "music.h"
#include "ui_music.h"

music::music(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::music)
{
    ui->setupUi(this);
    initbutton();


}

music::~music()
{
    delete ui;
}

void music::initbutton(){
    QPushButton *playbtn = new QPushButton(this);
    QPushButton *nextsongbtn = new QPushButton(this);
    QPushButton *presongbtn = new QPushButton(this);
    QPushButton *fileselectbtn = new QPushButton(this);
    QPushButton *playmodebtn = new QPushButton(this);

    playbtn->setIcon(QIcon(":/image/music/playback.png"));
    nextsongbtn->setIcon(QIcon(":/image/music/nextsong.png"));
    presongbtn->setIcon(QIcon(":/image/music/presong.png"));
    fileselectbtn->setIcon(QIcon(":/image/music/file.png"));
    playmodebtn->setIcon(QIcon(":/image/music/seqplay.png"));


    playbtn->setGeometry(565,700,70,70);
    playbtn->setIconSize(QSize(60,60));
    nextsongbtn->setGeometry(640,700,70,70);
    nextsongbtn->setIconSize(QSize(60,60));
    presongbtn->setGeometry(490,700,70,70);
    presongbtn->setIconSize(QSize(60,60));
    playmodebtn->setGeometry(40,700,70,70);
    playmodebtn->setIconSize(QSize(60,60));
    fileselectbtn->setGeometry(1100,700,70,70);
    fileselectbtn->setIconSize(QSize(60,60));

}
