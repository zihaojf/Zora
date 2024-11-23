#ifndef SCHOOLCLASS_H
#define SCHOOLCLASS_H

#include <QWidget>

namespace Ui {
class schoolclass;
}

class schoolclass : public QWidget
{
    Q_OBJECT

public:
    explicit schoolclass(QWidget *parent = nullptr);
    ~schoolclass();

private:
    Ui::schoolclass *ui;
};

#endif // SCHOOLCLASS_H
