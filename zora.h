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
    vector<QPixmap> standmap;
    QLabel *standImage;

public:
    Zora(QWidget *parent = nullptr);
    ~Zora();

    void standMovementLoad();//站立图片载入
    void jumpMovementLoad();//跳跃图片载入
    void lieMovementLoad();//趴下图片载入
    void tumbleMovementLoad();//翻滚图片载入

    void standMovement();//站立动作
    void jumpMovement();//跳跃动作
    void lieMovement();//趴下动作
    void tumbleMovement();//翻滚动作

private:
    Ui::Zora *ui;
};
#endif // ZORA_H
