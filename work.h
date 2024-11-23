#ifndef WORK_H
#define WORK_H

#include <QWidget>

namespace Ui {
class work;
}

class work : public QWidget
{
    Q_OBJECT

public:
    explicit work(QWidget *parent = nullptr);
    ~work();

private:
    Ui::work *ui;
};

#endif // WORK_H
