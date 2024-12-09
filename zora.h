#ifndef ZORA_H
#define ZORA_H

#include <QMainWindow>
#include<QMouseEvent>
#include<QtGlobal>
#include <QLabel>
#include<QPoint>
#include<QTimer>
#include<QPushButton>
#include<QCalendarWidget>
#include<QFile>
#include<QDataStream>
#include<QSystemTrayIcon>
#include<vector>
#include<QRandomGenerator>
#include<qobject.h>

#include"account.h"
#include"music.h"
#include"schoolclass.h"
#include"work.h"
#include"life.h"
#include"passwordlogin.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class Zora;
}
QT_END_NAMESPACE

class Zora : public QMainWindow
{
    Q_OBJECT

private:
    int body_size;//主形象的大小
    int button_size;//首页按钮的大小
    QTimer *timer;//记时
    vector<QPixmap> standMap;//站立图片容器
    vector<QPixmap> jumpMap;
    vector<QPixmap> lieMap;
    vector<QPixmap> tumbleMap;
    //QLabel标签指针
    QLabel *bodyImage;
    QPoint MoveTopLeft;//记录初始的移动左上坐标点

    //按钮
    QPushButton *closebtn;
    QPushButton *musicbtn;
    QPushButton *accountbtn;
    QPushButton *classbtn;
    QPushButton *workbtn;
    QPushButton *passwordbtn;
    QPushButton *lifebtn;
    QPushButton *minbtn;
    bool buttonswitch;//记录按钮显示还是隐藏

    //窗口
    account *account_window;
    music *music_window;
    schoolclass *class_window;
    work *work_window;
    life *life_window;
    passwordlogin *passwordlogin_window;

    QSystemTrayIcon* psystemtray;//任务栏最小化托盘



private slots://四个状态槽
    void standMovement();//站立动作
    void jumpMovement();//跳跃动作
    void lieMovement();//趴下动作
    void tumbleMovement();//翻滚动作

public:
    Zora(QWidget *parent = nullptr);
    ~Zora();

    void ImageLoad();//四种状态图片加载

    enum class AnimationState{//四种状态
        stand,
        jump,
        tumble,
        lie
    };
    AnimationState currentAnimation;//当前运动状态
    void timeoutHandler();//timeout触发器，选择接下来的动作
    void mousePressEvent(QMouseEvent *event);//鼠标点击切换状态
    void mouseMoveEvent(QMouseEvent *event);//鼠标长按左键移动位置

    void initbutton();//初始化按钮
    void setbutton_size();//设置按钮大小
    void setbutton_invisiable();//设置按钮初始默认隐藏

    //各个功能模块
    void closebtn_push();
    void musicbtn_push();
    void accountbtn_push();
    void classbtn_push();
    void workbtn_push();
    void passwordloginbtn_push();
    void lifebtn_push();
    void minbtn_push();

    void initpsystemtray();//初始化系统托盘
    void systemtray_push();//点击系统托盘事件


private:
    Ui::Zora *ui;
};
#endif // ZORA_H
