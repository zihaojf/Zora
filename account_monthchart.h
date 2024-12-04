#ifndef ACCOUNT_MONTHCHART_H
#define ACCOUNT_MONTHCHART_H

#include <QWidget>

namespace Ui {
class account_monthchart;
}

class account_monthchart : public QWidget
{
    Q_OBJECT

public:
    explicit account_monthchart(QWidget *parent = nullptr);
    ~account_monthchart();

private:
    Ui::account_monthchart *ui;
};

#endif // ACCOUNT_MONTHCHART_H
