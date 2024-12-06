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
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFileInfoList>
#include <QMediaPlaylist>
#include <QListWidget>
#include <QString>
#include <QPlainTextEdit>


namespace Ui {
class music;
}

class music : public QWidget
{
    Q_OBJECT

public:
    explicit music(QWidget *parent = nullptr);
    ~music();

    void init();
    void set_musicfilepath();//设置音乐文件路径
    void get_musicfile();//获取音乐文件
    void playmusiclistitem(QListWidgetItem *item);//双击播放音乐
    void playmusic();//播放音乐
    void pausemusic();//暂停
    void nextsong();//下一首
    void presong();//上一首
    void setplaymode();//设置播放顺序模式
    void show_current_musicname();//显示当前音乐名称
    void setstylesheet();//设置样式表

private:
    Ui::music *ui;
    //窗口大小：1200x800
    QPushButton *playbtn;//播放按钮
    QPushButton *pausebtn;//暂停按钮
    QPushButton *nextsongbtn;//下一首
    QPushButton *presongbtn;//上一首
    QPushButton *fileselectbtn;//选择文件夹
    QPushButton *playmodebtn;//播放顺序模式
    QString musicpath;//音乐路径
    QFileInfoList musicfilelist;//音乐名列表
    QStringList filelist;//文件名列表
    QMediaPlayer *player;//播放器
    QMediaPlaylist *playlist;//播放列表
    int playmode;//记录播放顺序模式1顺序2随机




};

#endif // MUSIC_H
