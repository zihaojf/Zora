#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui{class CardWidget;}
QT_END_NAMESPACE
class CardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardWidget(QWidget *parent = nullptr);

    void settitle(const QString &title);
    void setcontent(const QString &content);
    void settime(const QString &time);
    void setid(int id);
    int getid();
    void mousepress();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            emit clicked(widgetid);  // 发射点击信号
        }
        QWidget::mouseReleaseEvent(event);  // 调用基类的实现
    }


private:
    Ui::CardWidget *ui;
    QLabel *titlelabel;
    QLabel *contentlabel;
    QLabel *timelabel;
    int widgetid;

signals:
    void clicked(int id);
};

#endif // CARDWIDGET_H
