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
    QTimer *timer;//记时
    vector<QPixmap> standMap;//站立图片容器
    vector<QPixmap> jumpMap;
    vector<QPixmap> lieMap;
    vector<QPixmap> tumbleMap;
    //QLabel标签指针
    QLabel *standImage;
    QLabel *jumpImage;
    QLabel *lieImage;
    QLabel *tumbleImage;

public:
    Zora(QWidget *parent = nullptr);
    ~Zora();

    void ImageLoad();//四种状态图片加载

    void standMovement();//站立动作
    void jumpMovement();//跳跃动作
    void lieMovement();//趴下动作
    void tumbleMovement();//翻滚动作

private:
    Ui::Zora *ui;
};
#endif // ZORA_H
